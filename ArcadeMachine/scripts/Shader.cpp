#include "Shader.h"
#include "FileReader.h"
#include "ShaderManager.h"

Shader::Shader(std::string name, std::string path)
{
	InitShader(path);
	ShaderManager::addShader(name, this);
}

Shader::Shader(std::string path)
{
	InitShader(path);
}

void Shader::use()
{
	glUseProgram(m_ProgramID);
}

GLint Shader::findProperty(string prop)
{
	return glGetUniformLocation(m_ProgramID, prop);
}

bool Shader::hasProperty(string prop)
{
	return glGetUniformLocation(m_ProgramID, prop) != -1;
}

GLuint Shader::get_Program()
{
	return m_ProgramID;
}

void Shader::InitShader(std::string path)
{
	Debug::sectionBegin("Shader");
	Debug::log("Creating shader : " + path);

	std::string vertexPath = std::string(path + ".vert");
	std::string fragmentPath = std::string(path + ".frag");

	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode = FileReader::openFile(vertexPath);
	if (vertexShaderCode == "") {
		Debug::error("Impossible to open the file " + std::string(vertexPath));
		return;
	}

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode = FileReader::openFile(fragmentPath);
	if (vertexShaderCode == "") {
		Debug::error("Impossible to open the file " + std::string(fragmentPath));
		return;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	Debug::log("Compiling shader : " + vertexPath);
	char const * VertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		if (strlen(&VertexShaderErrorMessage[0]) > 1)
		{
			Debug::error(&VertexShaderErrorMessage[0]);
		}
	}



	// Compile Fragment Shader
	Debug::log("Compiling shader : " + fragmentPath);
	char const * FragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		if (strlen(&FragmentShaderErrorMessage[0]) > 1)
		{
			Debug::error(&FragmentShaderErrorMessage[0]);
		}
	}


	// Link the program
	Debug::log("Linking program");
	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, vertexShaderID);
	glAttachShader(m_ProgramID, fragmentShaderID);
	glLinkProgram(m_ProgramID);

	// Check the program
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(m_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		if (strlen(&ProgramErrorMessage[0]) > 1)
		{
			Debug::error(&ProgramErrorMessage[0]);
		}
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	Debug::sectionEnd("Shader");
}
