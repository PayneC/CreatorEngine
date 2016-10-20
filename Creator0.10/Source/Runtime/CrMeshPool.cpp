#include "CrMeshPool.h"
#include "CrEngine.h"

#include <fbxsdk.h>

CrMeshPool::CrMeshPool()
{
}

CrMeshPool::~CrMeshPool()
{
	
}

bool CrMeshPool::Init()
{

	return true;
}

CrMeshChunk * CrMeshPool::MeshCube()
{
	if (m_pMeshCube)
		return m_pMeshCube;

	m_pMeshCube = new CrMeshChunk();

	GLfloat cube_positions[] =
	{
		-0.5f, -0.5f, -0.5f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f,
	};

	GLfloat cube_colors[] =
	{
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,
	};

	GLushort cube_indices[] =
	{
		0,1,2,3,6,7,4,5,
		0xffff,
		2,6,0,4,1,5,3,7,
	};

	m_pMeshCube->m_dVertexSize = sizeof(cube_positions);
	m_pMeshCube->m_dColorSize = sizeof(cube_colors);
	m_pMeshCube->m_dElementSize = sizeof(cube_indices);

	glGenBuffers(1, &m_pMeshCube->m_dElementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pMeshCube->m_dElementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_pMeshCube->m_dElementSize, cube_indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_pMeshCube->m_dVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_pMeshCube->m_dVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_pMeshCube->m_dVertexSize + m_pMeshCube->m_dColorSize, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, m_pMeshCube->m_dVertexSize, cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, m_pMeshCube->m_dVertexSize, m_pMeshCube->m_dColorSize, cube_colors);

	return m_pMeshCube;
}
CrMeshChunk * CrMeshPool::MeshTriangle()
{
	return nullptr;
}
CrMeshChunk * CrMeshPool::CreateMesh(std::string filename)
{
	std::string filetype = filename.substr(filename.find_last_of('.') + 1);
	
	if (filetype == "fbx")//暂时区分大小写
	{
		return CreateFromFbx(filename.c_str());
	}
	else if (filetype == "obj")
	{
		return CreateFromObj(filename.c_str());
	}

	return NULL;
}

CrMeshChunk * CrMeshPool::CreateFromFbx(const char* filename)
{
	CrMeshChunk * pChunk = NULL;

	return pChunk;
}

CrMeshChunk * CrMeshPool::CreateFromObj(const char* filename)
{
	CrMeshChunk * pChunk = NULL;

	return pChunk;
}

CrMeshChunk * CrMeshPool::InsertMesh(std::string name)
{
	m_itorMesh = m_pMeshs.find(name);
	if (m_itorMesh != m_pMeshs.end())
		return m_itorMesh->second;

	CrMeshChunk * pChunk = CreateMesh(name);
	if (pChunk)
		m_pMeshs.insert(std::pair<std::string, CrMeshChunk *>(name, pChunk));

	return pChunk;
}

CrMeshChunk * CrMeshPool::Find(std::string name)
{
	m_itorMesh = m_pMeshs.find(name);
	if (m_itorMesh != m_pMeshs.end())
		return m_itorMesh->second;

	return NULL;
}

void CrMeshPool::Remove(std::string name)
{
	m_itorMesh = m_pMeshs.find(name);
	if (m_itorMesh != m_pMeshs.end())
	{
		m_itorMesh->second->Release();
		m_pMeshs.erase(m_itorMesh);
	}
}

void CrMeshPool::RemoveAll()
{
	for (m_itorMesh = m_pMeshs.begin(); m_itorMesh != m_pMeshs.end(); ++m_itorMesh)
	{
		m_itorMesh->second->Release();
	}

	m_pMeshs.clear();
}

void CrMeshPool::ClearUpCustomMesh()
{
	for (m_itorMesh = m_pMeshs.begin(); m_itorMesh != m_pMeshs.end(); ++m_itorMesh)
	{
		while (m_itorMesh->second->GetUserNumber() < 2)
		{
			m_itorMesh->second->Release();
			m_itorMesh = m_pMeshs.erase(m_itorMesh);
		}
	}
}

void CrMeshPool::ClearUpDefaultMesh()
{
	if (m_pMeshCube && m_pMeshCube->GetUserNumber() < 2)
	{
		m_pMeshCube->Release();
		m_pMeshCube = NULL;
	}
}