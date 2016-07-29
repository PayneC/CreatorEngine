#include "CrTextureUtility.h"
#include <SOIL.h>

CrTextureUtility::CrTextureUtility()
{
}

CrTextureUtility::~CrTextureUtility()
{
}

CrTexture * CrTextureUtility::LoadTexture(const char* filename, unsigned int hashCode, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	return NULL;
}

CrTexture * CrTextureUtility::LoadTexture(const char* filename)
{
	int width, height, channels;
	unsigned char * image = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);
	CrTexture * instance = new CrTexture();
	instance->m_dWidth = width;
	instance->m_dHeight = height;
	instance->m_dTextureId;

	size_t s = strlen(filename);
	size_t s2 = strlen((char *)image);

	glGenTextures(1, &(instance->m_dTextureId));
	glBindTexture(GL_TEXTURE_2D, instance->m_dTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (channels == SOIL_LOAD_RGBA)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}
	else if (channels == SOIL_LOAD_RGB)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE, 0);

	return instance;
}

/*
CrTexture * CrTextureUtility::LoadTexture(const char* filename, unsigned int hashCode, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	std::map<unsigned int, CrTexture*>::iterator iter = m_mapTexture.find(hashCode);
	//if this texture ID is in use, unload the current texture
	if (iter != m_mapTexture.end())
	{
		return (iter->second);
	}

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return NULL;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return NULL;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
	{
		return NULL;
	}

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use
	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		border, image_format, GL_UNSIGNED_BYTE, bits);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	CrTexture * texture = new CrTexture();
	texture->Retain();

	texture->m_dAnisoLevel = level;
	texture->m_dWidth = width;
	texture->m_dHeight = height;
	texture->m_dTextureId = gl_texID;

	//return success
	return texture;
}
*/