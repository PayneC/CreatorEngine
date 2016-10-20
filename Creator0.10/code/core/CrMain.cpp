/*
Mobius
function
2014/12/22
Payne
*/

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new(_CLIENT_BLOCK,__FILE__,__LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#include "CreatorEngine.h"
#include "CrTransform.h"
#include <iostream>

#include <ft2build.h>
#include <freetype\freetype.h>
#include <freetype\ftglyph.h>
#include <freetype\ftoutln.h>
#include <freetype\fttrigon.h>

#include <vector>
#include <string>

#include <thread>

#include "CrMeshUtility.h"
#include "CrShaderUtility.h"
#include "CrTextureUtility.h"
#include "test.h"
#include "testCamera.h"


using std::vector;
using std::string;
using namespace CreatorEngine;

void LuaTest()
{
	lua_State * _L = luaL_newstate();
	luaL_openlibs(_L);

	int nret = luaL_dofile(_L, "main.lua");
	if (nret != 0)
	{
		const char *pc = lua_tostring(_L, -1);
		std::cout << pc << "\n";
	}

	lua_getglobal(_L, "main");
	nret = lua_pcall(_L, 0, 0, 0);

	if (nret != 0)
	{
		const char *pc = lua_tostring(_L, -1);
		std::cout << pc << "\n";
	}

	lua_close(_L);
}

lua_State * _L = NULL;
char * m_cBuffer;

void DebugThread()
{
	m_cBuffer = new char[64];
	_L = luaL_newstate();
	luaL_openlibs(_L);
	RegistemerLuaAPI(_L);
	while (true)
	{
		std::cin.getline(m_cBuffer, 64);
		luaL_dostring(_L, m_cBuffer);
	}
}

int main(int argc, char **argv)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (Initialization() != 0)
		return 0;

	LuaTest();

	std::thread _DebugThread(DebugThread);
	_DebugThread.detach();

	CrTexture * texture = CrTextureUtility::Instance()->LoadTexture("001.png");
	
	CrScene * pScene = CrGameObject::CreateGameObject<CrScene>("test01");
	
	CrGameObject * go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");
	pScene->AddChild(go);
	
	go->AddComponent<test>();
	
	go->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	go->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	go->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	CrMeshRender * meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor(glm::vec4(1, 1, 1, 1));
	meshRender->GetMaterial()->SetpMainTexture(texture);
	
	CrCamera * pCamera = CrGameObject::CreateGameObject<CrCamera>("Camera");
	pScene->AddChild(pCamera);
	pCamera->GetTransform()->SetPosition(glm::fvec3(0.f, 0.f, 20.0f));
	
	pCamera->GetTransform()->LookAt(go);
	pCamera->AddComponent<testCamera>();
	
	CrTexture * texture2 = CrTextureUtility::Instance()->LoadTexture("TexMagic01.png");
	
	CrGameObject * go2 = NULL;
	for (int i = 0; i < 40; ++i)
	{
		for (int j = 0; j < 1; ++j)
		{
			for (int k = 0; k < 1; ++k)
			{
				go2 = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_CUBE, "cube");
				go->AddChild(go2);
				//go2->AddComponent<test>();
				go2->GetTransform()->SetLocalPosition(glm::vec3(-18 + i * 4, 0.f, 0.f));
				//go2->GetTransform()->SetLocalScale(glm::vec3(1.f, 1.f, 1.f));
				meshRender = go2->GetComponent<CrMeshRender>();
				meshRender->GetMaterial()->SetColor(glm::vec4((float)i / 10.f, (float)i / 10.f, (float)i / 10.f, 1.f));
				meshRender->GetMaterial()->SetpMainTexture(texture2);
			}
		}
	}
	
	
	go = CrGameObject::CreateGameObject<CrGameObject>(EPresetMeshType::CR_MESH_TYPE_QUAD, "center");
	pScene->AddChild(go);
	go->GetTransform()->SetPosition(glm::vec3(5, -5, 5));
	go->GetTransform()->SetLocalScale(glm::vec3(1, 1, 1));
	go->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	meshRender = go->GetComponent<CrMeshRender>();
	meshRender->GetMaterial()->SetColor(glm::vec4(1, 1, 1, 1));
	meshRender->GetMaterial()->SetpMainTexture(texture);
	
	Start(pScene);

	lua_close(_L);
	delete[] m_cBuffer;
	m_cBuffer = NULL;

	_CrtDumpMemoryLeaks();
	return 0;
}

#define fonttest
#ifndef fonttest

#define MAX_NO_TEXTURES 1

#define CUBE_TEXTURE 0

GLuint texture_id[MAX_NO_TEXTURES];

struct xCharTexture
{
	GLuint  m_texID;
	wchar_t m_chaID;
	int     m_Width;
	int     m_Height;

	int     m_adv_x;
	int     m_adv_y;
	int     m_delta_x;
	int     m_delta_y;
public:
	xCharTexture()
	{
		m_texID = 0;
		m_chaID = 0;
		m_Width = 0;
		m_Height = 0;
	}
}g_TexID[65536];


class xFreeTypeLib
{
	FT_Library m_FT2Lib;
	FT_Face    m_FT_Face;

public:
	int   m_w;
	int   m_h;
	void load(const char* font_file, int _w, int _h);
	GLuint loadChar(wchar_t ch);
};

void xFreeTypeLib::load(const char* font_file, int _w, int _h)
{
	FT_Library library;
	FT_Error rlt = 0;

	rlt = FT_Init_FreeType(&library);
	if (rlt != 0)
	{
		return;
	}

	//����һ������,ȡĬ�ϵ�Face,һ��ΪRegualer
	rlt = FT_New_Face(library, font_file, 0, &m_FT_Face);
	if (rlt != 0)
	{
		return;
	}

	//ѡ���ַ���
	FT_Select_Charmap(m_FT_Face, FT_ENCODING_UNICODE);

	m_w = _w; 
	m_h = _h;

	m_FT_Face->num_fixed_sizes;

	//��СҪ��64.���ǹ涨�������Ϳ����ˡ�
	FT_Set_Char_Size( m_FT_Face , 0 , m_w << 6, 96, 96);
	//�������ָ���ַ���Ⱥ͸߶ȵ��ض�����
	FT_Set_Pixel_Sizes(m_FT_Face, m_w, m_h);
}

GLuint xFreeTypeLib::loadChar(wchar_t ch)
{
	if (g_TexID[ch].m_texID)
		return g_TexID[ch].m_texID;
	/* װ������ͼ�����βۣ�����Ĩ����ǰ������ͼ�� */
	if (FT_Load_Char(m_FT_Face, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT |
		(TRUE ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO)))
	{
		return 0;
	}

	/*if(FT_Load_Glyph( m_FT_Face, FT_Get_Char_Index( m_FT_Face, ch ), FT_LOAD_FORCE_AUTOHINT ))
	throw std::runtime_error("FT_Load_Glyph failed");*/

	xCharTexture& charTex = g_TexID[ch];

	//�õ���ģ
	FT_Glyph glyph;
	//������ͼ������β۸��Ƶ��µ�FT_Glyph����glyph�С������������һ�������벢������glyph�� 
	if (FT_Get_Glyph(m_FT_Face->glyph, &glyph))
		return 0;

	//ת����λͼ
	FT_Render_Glyph(m_FT_Face->glyph, FT_RENDER_MODE_LCD);//FT_RENDER_MODE_NORMAL  ); 
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//ȡ��λͼ����
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	//��λͼ���ݿ����Լ��������������.�����ɿ��Ի�����Ҫ�Ķ��������ˡ�
	int width = bitmap.width;
	int height = bitmap.rows;

	m_FT_Face->size->metrics.y_ppem;		//�������뵽�豸�ռ�
	m_FT_Face->glyph->metrics.horiAdvance;  //ˮƽ�ı�����


	charTex.m_Width = width;
	charTex.m_Height = height;
	charTex.m_adv_x = m_FT_Face->glyph->advance.x / 64.0f;  //�������
	charTex.m_adv_y = m_FT_Face->size->metrics.y_ppem;		//m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
	charTex.m_delta_x = (float)bitmap_glyph->left;			//left:����ԭ��(0,0)������λͼ��������ص�ˮƽ����.�����������ص���ʽ��ʾ�� 
	charTex.m_delta_y = (float)bitmap_glyph->top - height;	//Top: ���������β۵�bitmap_top�ֶΡ�
	glGenTextures(1, &charTex.m_texID);
	glBindTexture(GL_TEXTURE_2D, charTex.m_texID);
	char* pBuf = new char[width * height * 4];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned char _vl = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
			pBuf[(4 * i + (height - j - 1) * width * 4)] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 1] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 2] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 3] = _vl;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //ָ��һ����ά������ͼƬ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():�������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);								//������л��

	/*gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE);*/
	delete[] pBuf;
	return charTex.m_chaID;
}


xFreeTypeLib g_FreeTypeLib;
float ratio;

xCharTexture* getTextChar(wchar_t ch)
{
	g_FreeTypeLib.loadChar(ch);
	return &g_TexID[ch];
}



//wchar_t g_UnicodeString[]=L"aaabb/x4E2D/x6587/x0031/x0032/x0033";  
const char g_UnicodeString[] = "aaa VB�ļ���ʽ��/n/������ȷ�ͱ�Ϊδ֪/n/�����ߣ�";


void drawText(wchar_t* _strText, int x, int y, int maxW, int h)
{
	int sx = x;
	int sy = y;
	int maxH = h;
	size_t nLen = wcslen(_strText);

	for (int i = 0; i <nLen; i++)
	{
		if (_strText[i] == '/n')
		{
			sx = x; sy += maxH + 12;
			continue;
		}
		xCharTexture* pCharTex = getTextChar(_strText[i]);
		glBindTexture(GL_TEXTURE_2D, pCharTex->m_texID);							//�󶨵�Ŀ������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glEnable(GL_BLEND);														//�򿪻�ر�OpenGL�����⹦��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);						//����������㷨
		//glDisable(GL_TEXTURE_2D);
		int w = pCharTex->m_Width;
		int h = pCharTex->m_Height;

		int ch_x = sx + pCharTex->m_delta_x;
		int ch_y = sy - h - pCharTex->m_delta_y;

		if (maxH < h) maxH = h;
		glBegin(GL_QUADS);													 // ����һ����һ��ԭʼ�Ķ���
		{
			glTexCoord2f(0.0f, 1.0f); glVertex3f(ch_x, ch_y, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(ch_x + w, ch_y, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(ch_x + w, ch_y + h, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(ch_x, ch_y + h, 1.0f);
		}
		glEnd();
		sx += pCharTex->m_adv_x;
		if (sx > x + maxW)
		{
			sx = x; sy += maxH + 12;
		}
	}
}

void init(void)
{
	glShadeModel(GL_SMOOTH | GL_FLAT);						//ѡ��ƽֱ��ƽ����ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					//���ɫ�ʻ�����
	glEnable(GL_COLOR_MATERIAL_FACE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	// ʹһ������ɫ��ָ��ǰ��ɫ��

	//g_FreeTypeLib.load("simhei.ttf",14,14);
	// g_FreeTypeLib.load("c://windows//fonts//simhei.ttf",14,14);
	g_FreeTypeLib.load("c://windows//fonts//simhei.ttf", 12, 12);

	glDisable(GL_CULL_FACE);

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);							//�������
	glLoadIdentity();										//�ú�Ⱦ����滻��ǰ����

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);								//�����Ӵ�
	glOrtho(0, w, h, 0, -100, 200);							//�ô�ֱ�����뵱ǰ�������
	// Set the clipping volume
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30, 0, 0, 10, 0.0f, 1.0f, 0.0f);	//�趨һ���任�ӵ�
}

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glLoadIdentity ( );
	glPushMatrix();
	glTranslatef ( 0.0, 0.0, -5.0 );
	*/
	glEnable(GL_TEXTURE_2D);
	wchar_t *wstr = AnsiToUnicode(g_UnicodeString);
	drawText(wstr, 50, 50, 900, 25);
	//glPopMatrix();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 27:        // When Escape Is Pressed...
		exit(0);   // Exit The Program
		break;        // Ready For Next Case
	default:        // Now Wrap It Up
		break;
	}
}

void myDisplay(void)

{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(180, 15);
	glVertex2i(10, 145);
	glEnd();

	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	glFlush();

}

int main(int argc, char * argv[])
{

	//ANSI�ַ��������ݳ���7�ֽ�   
	char sz[20] = "����123";

	//UNICODE�ַ��������ݳ���5��wchar_t��10�ֽڣ�   
	wchar_t   wsz[100] = L"/x4E2D/x6587/x0031/x0032/x0033";
	//����ʱ�趨��ǰANSI���룬VC��ʽ   
	setlocale(LC_ALL, ".936");

	//GCC�и�ʽ   
	setlocale(LC_ALL, "zh_CN.GBK");

	//VisualC++��ʹ��Сд%s������setlocaleָ������������ļ�   
	//GCC��ʹ�ô�д%S   


	//��UNICODE�ַ�������setlocaleָ���ı���ת�����ֽ�   
	wcstombs(sz, wsz, 20);
	//���ֽڴ�����setlocaleָ���ı���ת����UNICODE�ַ���   
	mbstowcs(wsz, sz, 20);

// 	glutInit(&argc, argv);									   //���ڳ�ʼ��GULT��
// 	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  //���ó�ʼ��ʾģʽ
// 	glutInitWindowPosition(0, 0);								   //ȷ�����ڵ�λ��
// 	glutInitWindowSize(900, 500);							   //���ô��ڴ�С
// 	glutCreateWindow("NeHe Lesson 6- Ported by Rustad");	   //����һ�����ڱ���
	init();
	//glutFullScreen      ( );          //Put Into Full Screen
// 	glutDisplayFunc(display);	//ע��һ����ͼ����
// 	glutReshapeFunc(reshape);	//����ͶӰ�ĺ���
// 	glutKeyboardFunc(keyboard);	//���̻ص�����
// 	glutSpecialFunc(arrow_keys);	//���õ�ǰ���ڵ�������̻ص���
// 	glutIdleFunc(display);		//�������ʱ���õĺ���
// 	glutMainLoop();			// ����GLUT�¼�����ѭ��

	return 0;

}
#endif // !fonttest