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
#include "CrCubemap.h"
#include "CrTexture.h"
#include <CrSingleton.h>

class DLL_ClASS CrTextureUtility : public CrSingleton<CrTextureUtility>
{
public:
	CrTextureUtility();
	~CrTextureUtility();

public:
	SharedPtr<CrTexture> LoadTexture(const char* filename, unsigned int hashCode, GLenum image_format, GLint internal_format, GLint level, GLint border);
	SharedPtr<CrTexture> LoadTexture(const char* filename);
private:
	std::map<unsigned int, SharedPtr<CrTexture>> m_mapTexture;
};

#endif