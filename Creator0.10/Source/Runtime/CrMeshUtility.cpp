#include "CrMeshUtility.h"
#include "CrShaderUtility.h"
#include "CrTextureUtility.h"
#include <CrMeshRender.h>
#include <CrTransform.h>

CrMeshUtility::CrMeshUtility()
{
}

CrMeshUtility::~CrMeshUtility()
{
}

SharedPtr<CrMesh> CrMeshUtility::CreateMesh(EPresetMeshType meshType)
{
	switch (meshType)
	{
	case CR_MESH_TYPE_CUBE:
		return CrMeshUtility::Instance()->CreateMeshCube();
	case CR_MESH_TYPE_QUAD:
		return CrMeshUtility::Instance()->CreateMeshQuad();
	default:
		return NULL;
	}
}

SharedPtr<CrMesh> CrMeshUtility::CreateMeshCube()
{
	if (m_BuiltinMeshs[CR_MESH_TYPE_CUBE] != NULL)
		return m_BuiltinMeshs[CR_MESH_TYPE_CUBE];

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE] = std::make_shared<CrMesh>();

	GLfloat vertices[] =
	{
		0.5, -0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5,
		0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
		-0.5, -0.5, -0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5,
		0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, -0.5, 0.5,
		-0.5, -0.5, 0.5,
		-0.5, -0.5, -0.5,
		-0.5, -0.5, 0.5,
		-0.5, 0.5, 0.5,
		-0.5, 0.5, -0.5,
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,
		0.5, 0.5, 0.5,
		0.5, -0.5, 0.5,
	};

	GLfloat normals[] =
	{
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 1, 0,
		0, 1, 0,
		0, 0, -1,
		0, 0, -1,
		0, 1, 0,
		0, 1, 0,
		0, 0, -1,
		0, 0, -1,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
	};

	GLfloat uvs[] =
	{
		0, 0,
		1, 0,
		0, 1,
		1, 1,
		0, 1,
		1, 1,
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		0, 0,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
	};

	GLuint triangles[] =
	{
		0, 2, 3, 0, 3, 1, 8, 4, 5, 8, 5, 9, 10, 6, 7, 10, 7, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23,
	};

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	size_t verticeSize = sizeof(vertices);
	size_t normalSize = sizeof(normals);
	size_t uvSize = sizeof(uvs);

	size_t triangleSize = sizeof(triangles);

	//VertexBufferObject
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticeSize + normalSize + uvSize, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, verticeSize, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize, normalSize, normals);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize + normalSize, uvSize, uvs);

	//ElementBufferObject
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleSize, triangles, GL_STATIC_DRAW);

	//VertexArrayObject
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		0,		  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,		  // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0,		  // stride
		(void *)0 // array buffer offset
		);

	glEnableVertexAttribArray(1); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		1,					// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		0,					// stride
		(void *)verticeSize // array buffer offset
		);

	glEnableVertexAttribArray(2); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		2,												 // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,												 // size
		GL_FLOAT,										 // type
		GL_FALSE,										 // normalized?
		0,												 // stride
		(void *)(verticeSize + normalSize) // array buffer offset
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindVertexArray(0);

	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetVAO(VAO);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetVBO(VBO);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetEBO(EBO);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetElementCount(triangleSize);
	m_BuiltinMeshs[CR_MESH_TYPE_CUBE]->SetName("cube");

	return m_BuiltinMeshs[CR_MESH_TYPE_CUBE];
}

SharedPtr<CrMesh> CrMeshUtility::CreateMeshQuad()
{
	if (m_BuiltinMeshs[CR_MESH_TYPE_QUAD] != NULL)
		return m_BuiltinMeshs[CR_MESH_TYPE_QUAD];

	m_BuiltinMeshs[CR_MESH_TYPE_QUAD] = std::make_shared<CrMesh>();

	GLfloat vertices[] =
	{
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	GLfloat normals[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	GLfloat uvs[] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	GLuint triangles[] =
	{
		0, 1, 3,
		0, 3, 2,
	};

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	size_t verticeSize = sizeof(vertices);
	size_t normalSize = sizeof(normals);
	size_t uvSize = sizeof(uvs);

	size_t triangleSize = sizeof(triangles);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticeSize + normalSize + uvSize, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, verticeSize, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize, normalSize, normals);
	glBufferSubData(GL_ARRAY_BUFFER, verticeSize + normalSize, uvSize, uvs);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleSize, triangles, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		0,		  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,		  // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0,		  // stride
		(void *)0 // array buffer offset
		);

	glEnableVertexAttribArray(1); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		1,					// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,					// size
		GL_FLOAT,			// type
		GL_FALSE,			// normalized?
		0,					// stride
		(void *)verticeSize // array buffer offset
		);

	glEnableVertexAttribArray(2); //attribute 0. No particular reason for 0, but must match the layout in the shader.
	glVertexAttribPointer(
		2,								   // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,								   // size
		GL_FLOAT,						   // type
		GL_FALSE,						   // normalized?
		0,								   // stride
		(void *)(verticeSize + normalSize) // array buffer offset
		);

	glBindVertexArray(0);

	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetVAO(VAO);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetVBO(VBO);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetEBO(EBO);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetElementCount(triangleSize);
	m_BuiltinMeshs[CR_MESH_TYPE_QUAD]->SetName("cube");

	return m_BuiltinMeshs[CR_MESH_TYPE_QUAD];
}

SharedPtr<CrGameObject> CrMeshUtility::LoadModel(const char* filename)
{
	Assimp::Importer _importer;
	const aiScene* pScene = _importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	SharedPtr<CrGameObject> _go = processNode(pScene->mRootNode, pScene);
	
	_importer.FreeScene();
	return _go;
}

SharedPtr<CrGameObject> CrMeshUtility::processNode(aiNode *node, const aiScene *scene)
{		
	SharedPtr<CrGameObject> _go = CrGameObject::CreateGameObject<CrGameObject>(node->mName.C_Str());
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		SharedPtr<CrGameObject> _goMesh = processMesh(mesh, scene);
		_goMesh->SetParent(_go);
		_goMesh->get_transform()->SetPosition(glm::vec3(0, 1, 0));
		_goMesh->get_transform()->SetLocalScale(glm::vec3(1, 1, 1));
		_goMesh->get_transform()->SetRotation(glm::vec3(0, 0, 0));
	}

	for (int i = 0; i < node->mNumChildren; ++i)
	{
		SharedPtr<CrGameObject> _goChild = processNode(node->mChildren[i], scene);
		_goChild->SetParent(_go);
		_goChild->get_transform()->SetPosition(glm::vec3(0, 1, 0));
		_goChild->get_transform()->SetLocalScale(glm::vec3(1, 1, 1));
		_goChild->get_transform()->SetRotation(glm::vec3(0, 0, 0));
	}

	return _go;
}

SharedPtr<CrGameObject> CrMeshUtility::processMesh(aiMesh *mesh, const aiScene *scene)
{	
	SharedPtr<CrGameObject> _go = CrGameObject::CreateGameObject<CrGameObject>(mesh->mName.C_Str());
	SharedPtr<CrMeshRender> meshRender = _go->AddComponent<CrMeshRender>();

	SharedPtr<CrMesh>  _mesh = std::make_shared<CrMesh>();
	SharedPtr<CrMaterial> material = CrMaterial::CreateCrMaterial();
	SharedPtr<CrShader> shader = CrShaderUtility::CreateShader("Blinn-Phong.vert", "Blinn-Phong.frag");
	material->SetShader(shader);
	meshRender->SetMaterial(material);
	meshRender->SetMesh(_mesh);

	material->SetColor("vBaseColor", glm::vec4(1, 1, 1, 1));

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex _vertex;
		_vertex.Position.x = mesh->mVertices[i].x;
		_vertex.Position.y = mesh->mVertices[i].y;
		_vertex.Position.z = mesh->mVertices[i].z;

		_vertex.Normal.x = mesh->mNormals[i].x;
		_vertex.Normal.y = mesh->mNormals[i].y;
		_vertex.Normal.z = mesh->mNormals[i].z;

		_vertex.Tangent.x = mesh->mTangents[i].x;
		_vertex.Tangent.y = mesh->mTangents[i].y;
		_vertex.Tangent.z = mesh->mTangents[i].z;

		_vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
		_vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;		

		_mesh->vertices.push_back(_vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			_mesh->indices.push_back(face.mIndices[j]);
	}
	
	_mesh->SetupMesh();

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* _material = scene->mMaterials[mesh->mMaterialIndex];
		const char * path;
		SharedPtr<CrTexture> texture;
		aiString str;
		_material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
		if (str.length > 0)
		{
			path = str.C_Str();
			texture = CrTextureUtility::Instance()->LoadTexture(path);
			//material->SetpMainTexture(texture);
			material->SetTexture("diffuse", texture, GL_TEXTURE0, 0);
		}

		str.Clear();
		_material->GetTexture(aiTextureType_SPECULAR, 0, &str);
		if (str.length > 0)
		{
			path = str.C_Str();
			texture = CrTextureUtility::Instance()->LoadTexture(path);
			//material->SetpSpecularTexture(texture);
			material->SetTexture("specular", texture, GL_TEXTURE2, 2);
		}
				
		str.Clear();
		_material->GetTexture(aiTextureType_HEIGHT, 0, &str);
		if (str.length > 0)
		{
			path = str.C_Str();
			texture = CrTextureUtility::Instance()->LoadTexture(path);
			//material->SetpNormalTexture(texture);
			material->SetTexture("normal", texture, GL_TEXTURE1, 1);
		}

		str.Clear();
	}	


	return _go;
}