/*
CreatorEngine
Class CrMaterial : CrObject
Payne
*/

#ifndef _CREATOR_MATERIAL_H
#define _CREATOR_MATERIAL_H

#include <CrDefine.h>
#include <CrComponent.h>
#include <string>
#include <CrShader.h>

class CrMaterial : public CrObject
{
public:
	CrMaterial();
	~CrMaterial();

private:
	CrShader * m_pShader;
	

};


#endif