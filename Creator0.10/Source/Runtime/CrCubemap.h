/*
CreatorEngine
Class CrTextureChunk
Payne
*/

#ifndef _CREATOR_CUBEMAP_H
#define _CREATOR_CUBEMAP_H

#include <CrMaterial.h>

class CrCubemap : public CrTexture
{
public:
	CrCubemap();
	~CrCubemap();

public:
	CrCubemap * CreateInstance(const char* filename);
	CrCubemap * CreateInstance(const char* _forward, const char* _back, const char* _up, const char* _down, const char* _left, const char* _right);
	//EasyGet(GLuint, m_dTextureId, TextureId)
	GLuint m_dTextureId;
private:

	int m_dAnisoLevel;
	int m_dWidth;
	int m_dHeight;
};

#endif