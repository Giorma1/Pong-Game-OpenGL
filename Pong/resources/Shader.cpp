#include <headers/Shader.h>

Shader::Shader(const char* VertexShaderPath, const char* FragmentShaderPath)
{
	std::string vertexCode, fragmentCode;
	std::fstream vertexFile, fragmentFile;
	std::stringstream vertexStream, fragmentStream;

	vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		vertexFile.open(VertexShaderPath);
		fragmentFile.open(FragmentShaderPath);

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();

	}
	catch (const std::exception&)
	{
		std::cout << "Shader File Cant Readed ";
	}

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ID = glCreateProgram();


	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
}

void Shader::UseProgram()
{
	glUseProgram(ID);
}

void Shader::DeleteProgram()
{
	glDeleteProgram(ID);
}