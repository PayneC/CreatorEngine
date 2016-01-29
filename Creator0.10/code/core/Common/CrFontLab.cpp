#include <Common/CrFontLab.h>

CrFontLab::CrFontLab()
{
}

CrFontLab::~CrFontLab()
{
}

bool CrFontLab::Init()
{
	load("simsunb.ttf", 12, 12);

	return true;
}

void CrFontLab::load(const char* font_file, int _w, int _h)
{
	FT_Error rlt = 0;

	rlt = FT_Init_FreeType(&m_FT2Lib);
	if (rlt)
		return;

	//����һ������,ȡĬ�ϵ�Face,һ��ΪRegualer
	rlt = FT_New_Face(m_FT2Lib, font_file, 0, &m_FT2Face);
	if (rlt)
		return;

	m_nWidth = _w;
	m_nHeight = _h;

	//ѡ���ַ���
	FT_Select_Charmap(m_FT2Face, FT_ENCODING_UNICODE);

	//��СҪ��64.���ǹ涨�������Ϳ����ˡ�
	FT_Set_Char_Size(m_FT2Face, m_nWidth << 6, m_nHeight << 6, 96, 96);
}


wchar_t CrFontLab::loadChar(wchar_t ch)
{
	if (m_pCharTexture[ch].m_wcharID)
		return m_pCharTexture[ch].m_wcharID;

	if(FT_Load_Glyph(m_FT2Face, FT_Get_Char_Index(m_FT2Face, ch), FT_LOAD_DEFAULT))
		return 0;

	CrCharTexture& charTex = m_pCharTexture[ch];

	//�õ���ģ
	FT_Glyph glyph;

	//������ͼ������β۸��Ƶ��µ�FT_Glyph����glyph�С������������һ�������벢������glyph�� 
	if (FT_Get_Glyph(m_FT2Face->glyph, &glyph))
		return 0;

	//ת����λͼ
	FT_Render_Glyph(m_FT2Face->glyph, FT_RENDER_MODE_NORMAL);//FT_RENDER_MODE_LCD  ); 
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//ȡ��λͼ����
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	//��λͼ���ݿ����Լ��������������.�����ɿ��Ի�����Ҫ�Ķ��������ˡ�
	int width = bitmap.width;
	int height = bitmap.rows;

	m_FT2Face->size->metrics.y_ppem;		//�������뵽�豸�ռ�
	m_FT2Face->glyph->metrics.horiAdvance;  //ˮƽ�ı�����

	charTex.m_nWidth = width;
	charTex.m_nHeight = height;
	charTex.m_adv_x = m_FT2Face->glyph->advance.x / 64.0f;  //�������
	charTex.m_adv_y = m_FT2Face->size->metrics.y_ppem;		//m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
	charTex.m_delta_x = (float)bitmap_glyph->left;			//left:����ԭ��(0,0)������λͼ��������ص�ˮƽ����.�����������ص���ʽ��ʾ�� 
	charTex.m_delta_y = (float)bitmap_glyph->top - height;	//Top: ���������β۵�bitmap_top�ֶΡ�
	glGenTextures(1, &charTex.m_uTextureID);
	glBindTexture(GL_TEXTURE_2D, charTex.m_uTextureID);

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

	delete[] pBuf;
	return charTex.m_wcharID;
}

CrCharTexture CrFontLab::GetCharTexture(wchar_t ch)
{
	wchar_t _index = loadChar(ch);
	return m_pCharTexture[_index];
}

void CrFontLab::Render(wchar_t* _strText, int x, int y, int maxW, int h)
{
	int sx = x;
	int sy = y;
	int maxH = h;
	size_t nLen = wcslen(_strText);

	for (int i = 0; i < nLen; i++)
	{
		if (_strText[i] == '/n')
		{
			sx = x; sy += maxH + 12;
			continue;
		}
		CrCharTexture pCharTex = GetCharTexture(_strText[i]);
		glBindTexture(GL_TEXTURE_2D, pCharTex.m_uTextureID);							//�󶨵�Ŀ������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glEnable(GL_BLEND);														//�򿪻�ر�OpenGL�����⹦��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);						//����������㷨
		//glDisable(GL_TEXTURE_2D);
		int w = pCharTex.m_nWidth;
		int h = pCharTex.m_nHeight;

		int ch_x = sx + pCharTex.m_delta_x;
		int ch_y = sy - h - pCharTex.m_delta_y;

		if (maxH < h) maxH = h;
		glBegin(GL_QUADS);													 // ����һ����һ��ԭʼ�Ķ���
		{
			glTexCoord2f(0.0f, 1.0f); glVertex3f(ch_x, ch_y, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(ch_x + w, ch_y, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(ch_x + w, ch_y + h, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(ch_x, ch_y + h, 1.0f);
		}
		glEnd();
		sx += pCharTex.m_adv_x;
		if (sx > x + maxW)
		{
			sx = x; sy += maxH + 12;
		}
	}
}