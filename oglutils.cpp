#include "oglutils.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

// simple output OpenGL Caps
void output_opengl_caps()
{
	// opengl strings
	std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "GL_VENDOR:                   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GL_RENDERER:                 " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GL_VERSION:                  " << glGetString(GL_VERSION) << std::endl;
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
}