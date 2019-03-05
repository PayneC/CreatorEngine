#include "CrTexture.h"

CrTexture::CrTexture()
{
}

CrTexture::~CrTexture()
{
	glDeleteTextures(1, &m_dTextureId);
}