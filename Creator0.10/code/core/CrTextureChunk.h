/*
CreatorEngine
Class CrTextureChunk
Payne
*/

#ifndef _CREATOR_TEXTURECHUNK_H
#define _CREATOR_TEXTURECHUNK_H

#include "CrDefine.h"
#include "CrObject.h"

class CrTextureChunk : public CrObject
{
	friend class CrTexturePool;
public:
	CrTextureChunk();
	~CrTextureChunk();

private:
	GLuint m_dTextureId;

	int m_dWidth;
	int m_dHeight;
};

#endif