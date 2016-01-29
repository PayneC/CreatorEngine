//#include <fbxsdk.h>
//#include "CrMesh.h"
//#include "CrSingleton.h"
//
////#define FBXSDK_VERSION_STRING
//
//class CrLoadFBXDate : public CrSingleton<CrLoadFBXDate>
//{
//public:
//	bool Initialize();
//	bool LoadFbxFile(const char* fbxFileName);
//
//	CrMesh* LoadMesh(const char* fbxFileName);
//
//	void ProcessNode(FbxNode * pNode, CrMesh * meshParent);
//	void ProcessMesh(FbxNode * pNode, CrMesh * meshParent);
//	void ProcessSkeleton(FbxNode * pNode, CrMesh * meshParent);
//	void ProcessLight(FbxNode * pNode, CrMesh * meshParent);
//	void ProcessCamera(FbxNode * pNode, CrMesh * meshParent);
//	
//private:
//	FbxManager* m_pFbxManager;
//	FbxScene* m_pScene;
//	FbxImporter * m_pFbxImporter;
//	FbxNode * m_pRootNode;
//
//	struct CrVersion
//	{
//		int major;
//		int minor;
//		int revision;
//	} m_sdkVersion, m_fileVersion;
//
//	bool www;
//};
