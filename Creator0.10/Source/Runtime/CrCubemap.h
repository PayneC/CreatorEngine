/*
CreatorEngine
Class CrTextureChunk
Payne
*/

#ifndef _CREATOR_CUBEMAP_H
#define _CREATOR_CUBEMAP_H

#include "CrDefine.h"
#include "CrTexture.h"
#include <string>
#include <map>

class CrCubemap : public CrTexture
{
	friend class CrTextureUtility;

public:
	CrCubemap();
	~CrCubemap();

public:
	//EasyGet(GLuint, m_dTextureId, TextureId)
		GLuint m_dTextureId;
private:
	
	int m_dAnisoLevel;
	int m_dWidth;
	int m_dHeight;
};

#endif