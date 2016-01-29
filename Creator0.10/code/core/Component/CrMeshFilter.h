/*
CreatorEngine
Class CrMeshFilter : CrComponent
Payne
*/

#ifndef _CREATOR_MESHFILTER_H
#define _CREATOR_MESHFILTER_H

#include <CrDefine.h>
#include <CrComponent.h>
#include <string>
#include <CrMesh.h>

class CrMeshFilter : public CrComponent
{
public:
	static CrMeshFilter * Create(std::string filePath);
	static CrMesh * CreateCube();
public:
	CrMeshFilter();
	~CrMeshFilter();

public:
	CrMesh * m_pMesh;
private:
	

};


#endif