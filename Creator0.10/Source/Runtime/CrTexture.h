/*
CreatorEngine
Class CrTextureChunk
Payne
*/

#ifndef _CREATOR_TEXTURE_H
#define _CREATOR_TEXTURE_H

#include <CrObject.h>

class DLL_ClASS CrTexture : public CrObject
{
	friend class CrTextureUtility;

public:
	CrTexture();
	~CrTexture();

public:
	GLuint m_dTextureId;
	int GetWidth() { return m_dWidth; }
	int GetHeight() { return m_dHeight; }
	GLenum GetTextureType() { return eTextureType; }
	GLenum GetTextureFormat() { return eTextureFormat; }

private:
	int m_dAnisoLevel;
	int m_dWidth;
	int m_dHeight;
	GLenum eTextureType;
	GLenum eTextureFormat;
};

#endif