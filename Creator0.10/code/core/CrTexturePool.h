/*
CreatorEngine
Class CrTexturePool
Payne
*/

#ifndef _CREATOR_TEXTUREPOOL_H
#define _CREATOR_TEXTUREPOOL_H

#include <map>
#include <string>

#include "CrDefine.h"
#include "CrTextureChunk.h"

class CrTexturePool
{
public:
	CrTexturePool();
	~CrTexturePool();

	CrTextureChunk * CreateTexture(const char* filename);
private:
	CrTextureChunk * ReadPng(const char* filename);

	std::map<std::string, CrTextureChunk*> m_mapTexture;
	
};

#endif