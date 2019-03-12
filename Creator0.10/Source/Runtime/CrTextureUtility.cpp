#include "CrTextureUtility.h"

CrTextureUtility::CrTextureUtility()
{
}

CrTextureUtility::~CrTextureUtility()
{
}

SharedPtr<CrTexture> CrTextureUtility::LoadTexture(const char* filename, unsigned int hashCode, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	return NULL;
}

SharedPtr<CrTexture> CrTextureUtility::LoadTexture(const char* filename)
{
	int width, height, channels;
	unsigned char * image = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);
	SharedPtr<CrTexture> instance = std::make_shared<CrTexture>();
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

SharedPtr<CrTexture> CrTextureUtility::LoadCubMap(const char* _right, const char* _left, const char* _up, const char* _down, const char* _back, const char* _forward)
{
	int width, height, nrChannels;
	unsigned char *data;

	std::vector<const char *> texs;
	texs.push_back(_right);
	texs.push_back(_left);
	texs.push_back(_up);
	texs.push_back(_down);
	texs.push_back(_back);
	texs.push_back(_forward);

	SharedPtr<CrTexture> instance = std::make_shared<CrTexture>();

	glGenTextures(1, &(instance->m_dTextureId));
	glBindTexture(GL_TEXTURE_CUBE_MAP, instance->m_dTextureId);

	for (unsigned int i = 0; i < texs.size(); i++)
	{
		data = SOIL_load_image(texs[i], &width, &height, &nrChannels, SOIL_LOAD_AUTO);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		SOIL_free_image_data(data);
	}

	//设置纹理放大时的过滤方式 线性过滤
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//设置纹理缩小时的过滤方式 邻近过滤
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//设置纹理环绕方式 为重复
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

	return instance;
}