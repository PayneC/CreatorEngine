#include "CrShaderUtility.h"

#include "CrDefine.h"
#include <string>
#include <fstream>

SharedPtr<CrShader> CrShaderUtility::CreateShader(const char * vertexFile, const char * fragmentFile)
{
	return Instance()->_CreateShader(vertexFile, fragmentFile);
}

CrShaderUtility::CrShaderUtility()
{
}
CrShaderUtility::~CrShaderUtility()
{
}

GLuint CrShaderUtility::CompileShader(const char * vertexFile, const char * fragmentFile)
{
	GLuint programID = glCreateProgram();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	
	GLint result = GL_FALSE;
	GLint infoLogLength = 0;
	GLchar * errorMessage = NULL;

	// Read the Vertex Shader code from the file
	std::ifstream vertexShaderStream(vertexFile, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(vertexShaderStream, Line))
			vertexShaderCode += "\n" + Line;
		vertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::ifstream fragmentShaderStream(fragmentFile, std::ios::in);
	if (fragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(fragmentShaderStream, Line))
			fragmentShaderCode += "\n" + Line;
		fragmentShaderStream.close();
	}

	// Compile Vertex Shader
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);
	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	// Show Info
	if (GL_TRUE == result)
	{
		printf("Success compiling shader : %s\n", vertexFile);
	}
	else
	{
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		errorMessage = new GLchar[infoLogLength];
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, errorMessage);
		printf("error : %s\n", errorMessage);
		delete[] errorMessage;
		errorMessage = NULL;
	}

	// Compile Fragment Shader
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);
	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	if (GL_TRUE == result)
	{
		printf("Success compiling shader : %s\n", fragmentFile);
	}
	else
	{
		glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		errorMessage = new GLchar[infoLogLength];
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, errorMessage);
		printf("error : %s\n", errorMessage);
		delete[] errorMessage;
		errorMessage = NULL;
	}

	// Link the program
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	if (GL_TRUE == result)
	{
		fprintf(stdout, "Success linking programn \n");
	}
	else
	{
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		errorMessage = new GLchar[infoLogLength];
		glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage);
		printf("error : %s\n", errorMessage);
		delete[] errorMessage;
		errorMessage = NULL;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

bool CrShaderUtility::Init()
{
	m_shaders = std::map<std::string, SharedPtr<CrShader>>();
	return true;
}

SharedPtr<CrShader> CrShaderUtility::Find(std::string name)
{
	SharedPtr<CrShader> shader = NULL;

	m_iterShader = m_shaders.find(name);
	if (m_iterShader != m_shaders.end())
	{
		shader = m_iterShader->second;
	}
	return shader;
}

void CrShaderUtility::Remove(std::string name)
{
	m_shaders.erase(name);
}

void CrShaderUtility::RemoveAll()
{
	m_shaders.clear();
}

//TODO:shader name ����_ƬԪ
SharedPtr<CrShader> CrShaderUtility::_CreateShader(const char * vertexFile, const char * fragmentFile)
{
	SharedPtr<CrShader> shader = Find(vertexFile);	

	if (!Find(vertexFile))
	{
		shader = std::make_shared<CrShader>();
		GLuint shaderID = CompileShader(vertexFile, fragmentFile);
		
		shader->SetShaderID(shaderID);				
		m_shaders.insert(std::make_pair(vertexFile, shader));
	}
	
	return shader;
}