#include <CrCubemap.h>
#include <CrTextureUtility.h>

// CrCubemap * CrCubemap::CreateInstance(const char* filename)
// {
// 	int width, height, channels;
// 	unsigned char * image = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);
// 	CrCubemap * instance = new CrCubemap();
// 	instance->m_dWidth = width;
// 	instance->m_dHeight = height;
// 	instance->m_dTextureId;
// 
// 	size_t s = strlen(filename);
// 	size_t s2 = strlen((char *)image);
// 
// 	glGenTextures(1, &(instance->m_dTextureId));
// 	glBindTexture(GL_TEXTURE_CUBE_MAP, instance->m_dTextureId);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
// 
// 	if (channels == SOIL_LOAD_RGBA)
// 	{
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
// 	}
// 	else if (channels == SOIL_LOAD_RGB)
// 	{
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// 	}
// 
// 	SOIL_free_image_data(image);
// 	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
// 
// 	return instance;
// }

// SharedPtr<CrCubemap> CrCubemap::CreateInstance(const char* _right, const char* _left, const char* _up, const char* _down, const char* _back, const char* _forward)
// {
// 	int width, height, nrChannels;
// 	unsigned char *data;
// 
// 	std::vector<const char *> texs;
// 	texs.push_back(_right);
// 	texs.push_back(_left);
// 	texs.push_back(_up);
// 	texs.push_back(_down);
// 	texs.push_back(_back);
// 	texs.push_back(_forward);
// 	
// 	SharedPtr<CrCubemap> instance = std::make_shared<CrCubemap>();
// 
// 	glGenTextures(1, &(instance->m_dTextureId));
// 	glBindTexture(GL_TEXTURE_CUBE_MAP, instance->m_dTextureId);
// 
// 	for (unsigned int i = 0; i < texs.size(); i++)
// 	{
// 		data = SOIL_load_image(texs[i], &width, &height, &nrChannels, SOIL_LOAD_AUTO);
// 		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
// 		SOIL_free_image_data(data);
// 	}
// 
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
// 
// 	return instance;
// }

CrCubemap::CrCubemap()
{
}

CrCubemap::~CrCubemap()
{
}
