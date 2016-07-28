/*
CreatorEngine
Class CrTextureUtility
Payne
*/

#ifndef _CREATOR_TEXTUREUTILITY_H
#define _CREATOR_TEXTUREUTILITY_H

#include <map>
#include <string>

#include "CrDefine.h"
#include "CrTexture.h"
#include <CrSingleton.h>

class CrTextureUtility : public CrSingleton<CrTextureUtility>
{
public:
	CrTextureUtility();
	~CrTextureUtility();

public:
	CrTexture * LoadTexture(const char* filename, unsigned int hashCode, GLenum image_format, GLint internal_format, GLint level, GLint border);
	CrTexture * LoadTexture(const char* filename);
private:
	std::map<unsigned int, CrTexture*> m_mapTexture;
};

#endif