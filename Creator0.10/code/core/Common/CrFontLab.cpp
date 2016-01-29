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

	//加载一个字体,取默认的Face,一般为Regualer
	rlt = FT_New_Face(m_FT2Lib, font_file, 0, &m_FT2Face);
	if (rlt)
		return;

	m_nWidth = _w;
	m_nHeight = _h;

	//选择字符表
	FT_Select_Charmap(m_FT2Face, FT_ENCODING_UNICODE);

	//大小要乘64.这是规定。照做就可以了。
	FT_Set_Char_Size(m_FT2Face, m_nWidth << 6, m_nHeight << 6, 96, 96);
}


wchar_t CrFontLab::loadChar(wchar_t ch)
{
	if (m_pCharTexture[ch].m_wcharID)
		return m_pCharTexture[ch].m_wcharID;

	if(FT_Load_Glyph(m_FT2Face, FT_Get_Char_Index(m_FT2Face, ch), FT_LOAD_DEFAULT))
		return 0;

	CrCharTexture& charTex = m_pCharTexture[ch];

	//得到字模
	FT_Glyph glyph;

	//把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。 
	if (FT_Get_Glyph(m_FT2Face->glyph, &glyph))
		return 0;

	//转化成位图
	FT_Render_Glyph(m_FT2Face->glyph, FT_RENDER_MODE_NORMAL);//FT_RENDER_MODE_LCD  ); 
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//取道位图数据
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	//把位图数据拷贝自己定义的数据区里.这样旧可以画到需要的东西上面了。
	int width = bitmap.width;
	int height = bitmap.rows;

	m_FT2Face->size->metrics.y_ppem;		//伸缩距离到设备空间
	m_FT2Face->glyph->metrics.horiAdvance;  //水平文本排列

	charTex.m_nWidth = width;
	charTex.m_nHeight = height;
	charTex.m_adv_x = m_FT2Face->glyph->advance.x / 64.0f;  //步进宽度
	charTex.m_adv_y = m_FT2Face->size->metrics.y_ppem;		//m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
	charTex.m_delta_x = (float)bitmap_glyph->left;			//left:字形原点(0,0)到字形位图最左边象素的水平距离.它以整数象素的形式表示。 
	charTex.m_delta_y = (float)bitmap_glyph->top - height;	//Top: 类似于字形槽的bitmap_top字段。
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //指定一个二维的纹理图片
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);							   //glTexParameteri():纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);								//纹理进行混合

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
		glBindTexture(GL_TEXTURE_2D, pCharTex.m_uTextureID);							//绑定到目标纹理
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glEnable(GL_BLEND);														//打开或关闭OpenGL的特殊功能
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);						//特殊的像素算法
		//glDisable(GL_TEXTURE_2D);
		int w = pCharTex.m_nWidth;
		int h = pCharTex.m_nHeight;

		int ch_x = sx + pCharTex.m_delta_x;
		int ch_y = sy - h - pCharTex.m_delta_y;

		if (maxH < h) maxH = h;
		glBegin(GL_QUADS);													 // 定义一个或一组原始的顶点
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