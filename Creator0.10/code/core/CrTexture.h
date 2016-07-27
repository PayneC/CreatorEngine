/*
CreatorEngine
Class CrTextureChunk
Payne
*/

#ifndef _CREATOR_TEXTURE_H
#define _CREATOR_TEXTURE_H

#include "CrDefine.h"
#include "CrObject.h"
#include <string>
#include <map>

class CrTexture : public CrObject
{
	friend class CrTextureUtility;

public:
	CrTexture();
	~CrTexture();

private:
	GLuint m_dTextureId;
	int m_dAnisoLevel;
	int m_dWidth;
	int m_dHeight;
};

#endif