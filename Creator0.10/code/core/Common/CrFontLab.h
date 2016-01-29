/*
CreatorEngine
Class CrFontLab
Payne
*/

#ifndef _CREATOR_FONTLAB_H
#define _CREATOR_FONTLAB_H

#include <CrDefine.h>
#include <ft2build.h>
#include <freetype\freetype.h>
#include <freetype\ftglyph.h>
#include <freetype\ftoutln.h>
#include <freetype\fttrigon.h>
#include <CrSingleton.h>

struct CrCharTexture
{
	GLuint  m_uTextureID;
	wchar_t m_wcharID;
	int     m_nWidth;
	int     m_nHeight;

	int     m_adv_x;
	int     m_adv_y;
	int     m_delta_x;
	int     m_delta_y;
public:
	CrCharTexture()
	{
		m_uTextureID = 0;
		m_wcharID = 0;
		m_nWidth = 0;
		m_nHeight = 0;
	}
};


class CrFontLab : public CrSingleton<CrFontLab>
{
	CrCharTexture m_pCharTexture[65536];
	FT_Library m_FT2Lib;
	FT_Face    m_FT2Face;

	int   m_nWidth;
	int   m_nHeight;
public:
	CrFontLab();
	~CrFontLab();
public:
	bool Init();
	void load(const char* font_file, int _w, int _h);
	wchar_t loadChar(wchar_t ch);
	CrCharTexture GetCharTexture(wchar_t ch);

	void Render(wchar_t*, int x, int y, int maxW, int h);
};

#endif