#include "CrDefine.h"
#include "CrLoadFBXDate.h"

using namespace fbxsdk_2015_1;

bool CrLoadFBXDate::Initialize()
{
	// Initialize the SDK manager. This object handles all our meCrry management.
	m_pFbxManager = FbxManager::Create();

	if (!m_pFbxManager)
		return false;

	// Create the IO settings object.
	FbxIOSettings *ios = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	m_pFbxManager->SetIOSettings(ios);

	// Create a new scene so that it can be populated by the imported file.
	//m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	return true;
}

bool CrLoadFBXDate::LoadFbxFile(const char* fbxFileName)
{
	if (!m_pFbxManager)
		return false;

	//FbxManager::GetFileFormatVersion(m_sdkVersion.major, m_sdkVersion.minor, m_sdkVersion.revision);

	// Create an importer using the SDK manager.
	FbxImporter* importer = FbxImporter::Create(m_pFbxManager, "");

	// Use the first argument as the filename for the importer.
	bool importerStatus = false;
	importerStatus = importer->Initialize(fbxFileName, -1, m_pFbxManager->GetIOSettings());
	if (!importerStatus)
	{
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", importer->GetStatus().GetErrorString());
		return importerStatus;
	}

	m_pScene = FbxScene::Create(m_pFbxManager, "");
	importer->Import(m_pScene);
	importer->Destroy();

	//importer->GetFileVersion(m_fileVersion.major, m_fileVersion.minor, m_fileVersion.revision);
	
	m_pRootNode = m_pScene->GetRootNode();

	return importerStatus;
}

CrMesh* CrLoadFBXDate::LoadMesh(const char* fbxFileName)
{
	CrMesh * mesh = new CrMesh();
	if (mesh)
	{
		Initialize();
		LoadFbxFile(fbxFileName);
		size_t length = m_pRootNode->GetChildCount();
		for (size_t i = 0; i < length; i++)
		{
			ProcessNode(m_pRootNode->GetChild(i), mesh);
		}
	}

	return mesh;
}

void CrLoadFBXDate::ProcessNode(FbxNode * pNode, CrMesh * meshParent)
{
	FbxNodeAttribute * nodeAttribute = pNode->GetNodeAttribute();
	if (nodeAttribute)
	{
		FbxNodeAttribute::EType type = nodeAttribute->GetAttributeType();
		switch (type)
		{
		case fbxsdk_2015_1::FbxNodeAttribute::eUnknown:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eNull:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eMarker:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eSkeleton:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eMesh:
			ProcessMesh(pNode, meshParent);
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eNurbs:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::ePatch:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eCamera:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eCameraStereo:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eCameraSwitcher:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eLight:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eOpticalReference:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eOpticalMarker:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eNurbsCurve:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eTrimNurbsSurface:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eBoundary:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eNurbsSurface:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eShape:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eLODGroup:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eSubDiv:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eCachedEffect:
			break;
		case fbxsdk_2015_1::FbxNodeAttribute::eLine:
			break;
		default:
			break;
		}
	}

	CrMesh * meshNode = NULL;
	size_t length = pNode->GetChildCount();
	for (size_t i = 0; i < length; i++)
	{
		meshNode = NULL;
		meshNode = new CrMesh();
		if (meshNode)
		{
			meshParent->AddChild(meshNode);
			ProcessNode(pNode->GetChild(i), meshNode);
		}
	}
}

void CrLoadFBXDate::ProcessMesh(FbxNode * pNode, CrMesh * meshParent)
{
	FbxMesh * pMesh = pNode->GetMesh();
	if (!pMesh)
		return;
	//三角形数
	int polygonCount = pMesh->GetPolygonCount();
	//顶点数

	int vertexCount = 3 * polygonCount;

	glm::vec3 * pVertex = new glm::vec3[vertexCount];

	fbxsdk_2015_1::FbxVector4 * pCtrlPoint = pMesh->GetControlPoints();

	int count = 0;

	for (int i = 0; i < polygonCount; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			int ctrlPointIndex = pMesh->GetPolygonVertex(i, j);
			int vertexCurrent = i * 3 + j;
			pVertex[vertexCurrent].x = pCtrlPoint[ctrlPointIndex].mData[0];
			pVertex[vertexCurrent].y = pCtrlPoint[ctrlPointIndex].mData[1];
			pVertex[vertexCurrent].z = pCtrlPoint[ctrlPointIndex].mData[2];
			++count;
			printf("x = %f, y = %f, z = %f \n", pVertex[vertexCurrent].x, pVertex[vertexCurrent].y, pVertex[vertexCurrent].z, NULL);
		}
	}

	printf("count = %d \n", count, NULL);

	GLuint vbo, ebo = 0;
	int size = sizeof(glm::vec3) * vertexCount;
	//创建缓存对象
	glGenBuffers(1, &vbo);
	//将缓存对象buffer 绑定到缓存结合点
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//向缓存输入 和 输出数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertexCount, pVertex, GL_STATIC_DRAW);

	printf("size = %d vertexCount = %d sizeof = %d \n", size, vertexCount, sizeof(glm::vec3), NULL);

	meshParent->SetVboId(vbo);
	meshParent->SetEboId(ebo);

}

void CrLoadFBXDate::ProcessSkeleton(FbxNode * pNode, CrMesh * meshParent)
{

}
void CrLoadFBXDate::ProcessLight(FbxNode * pNode, CrMesh * meshParent)
{

}
void CrLoadFBXDate::ProcessCamera(FbxNode * pNode, CrMesh * meshParent)
{

}

//ReadVertex(pMesh, ctrlPointIndex, &vertex[j]);

 // // Read the color of each vertex  
 // ReadColor(pMesh, ctrlPointIndex, vertexCounter, &color[j]);

 // // Read the UV of each vertex  
 // for (int k = 0; k < 2; ++k)
 // {
 //         ReadUV(pMesh, ctrlPointIndex, pMesh->GetTextureUVIndex(i, j), k, &(uv[j][k]));
 //     }

 // // Read the normal of each vertex  
 // ReadNormal(pMesh, ctrlPointIndex, vertexCounter, &normal[j]);

 // // Read the tangent of each vertex  
 // ReadTangent(pMesh, ctrlPointIndex, vertexCounter, &tangent[j]);
