/*
CreatorEngine
Class CrMaterial : CrObject
Payne
*/

#ifndef _CREATOR_MATERIAL_H
#define _CREATOR_MATERIAL_H

#include <CrDefine.h>
#include <Component\CrComponent.h>
#include <string>
#include <CrShader.h>
#include <CrTexture.h>

class CrMaterial : public CrObject
{
public:
	static CrMaterial * CreateCrMaterial();

public:
	CrMaterial();
	~CrMaterial();

public:


public:
	EasyGetSet(CrShader *, m_pShader, Shader);
	EasyGet(glm::vec4 , m_dColor, Color);
	EasyGetSet(CrTexture *, m_pMainTexture, pMainTexture);
	EasyGetSet(glm::vec2, m_v2mainTextureOffset, mainTextureOffset);
	EasyGetSet(glm::vec2, m_v2mainTextureScale, mainTextureScale);
	void SetColor(glm::vec4 & color);
private:
	void UploadUniform();
};


#endif