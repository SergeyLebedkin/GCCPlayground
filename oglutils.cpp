#include "oglutils.hpp"

#include <iostream>
#include <vector>

// simple output OpenGL Caps
void output_opengl_caps()
{
	// opengl strings
	std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "GL_VENDOR:                   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GL_RENDERER:                 " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GL_VERSION:                  " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL_EXTENSIONS:               " << glGetString(GL_EXTENSIONS) << std::endl;
	std::cout << std::endl;

	// output extentions line by line
	const char* str = (const char*)glGetString(GL_EXTENSIONS);
	while(*str++) *str == ' ' ? std::cout << std::endl : std::cout << *str;
	std::cout << std::endl;

	// some opengl capabilities
	GLint value = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
	std::cout << "GL_MAX_VERTEX_ATTRIBS:             " << value << std::endl;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &value);
	std::cout << "GL_MAX_VERTEX_UNIFORM_VECTORS:     " << value << std::endl;
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &value);
	std::cout << "GL_MAX_FRAGMENT_UNIFORM_VECTORS:   " << value << std::endl;
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &value);
	std::cout << "GL_MAX_RENDERBUFFER_SIZE:          " << value << std::endl;
	glGetIntegerv(GL_MAX_VARYING_VECTORS, &value);
	std::cout << "GL_MAX_VARYING_VECTORS:            " << value << std::endl;
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &value);
	std::cout << "GL_NUM_COMPRESSED_TEXTURE_FORMATS: " << value << std::endl;
	std::cout << std::endl;
}

// shader statuc check
bool shader_status_check(GLuint shader)
{
    GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLsizei maxLength = 0;
		GLsizei length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &length, &errorLog[0]);
		std::cout << errorLog.data() << std::endl;
		return false;
	}
	return true;
}