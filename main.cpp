#include <iostream>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "oglutils.hpp"

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text = R"(
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
varying vec3 color;
void main()
{
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    color = vCol;
}
)";

static const char* fragment_shader_text = R"(
precision lowp float;
varying vec3 color;
void main()
{
    gl_FragColor = vec4(color, 1.0);
}
)";

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	output_opengl_caps();

    // NOTE: OpenGL error checks have been omitted for brevity
    GLuint vertex_buffer = 0;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // create shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint isCompiledVert = 0;
    GLint isCompiledFrag = 0;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiledVert);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiledFrag);
	std::cout << "check shader info: " << std::endl;
	if((isCompiledVert == GL_FALSE) || (isCompiledFrag == GL_FALSE))
	{
		std::cout << "check shader vertex: " <<  isCompiledVert << std::endl;
		GLint maxLengthVert = 0;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLengthVert);
		std::cout << "maxLengthVert: " << maxLengthVert << std::endl;
		std::vector<GLchar> errorLogVert(maxLengthVert);
		glGetShaderInfoLog(vertex_shader, maxLengthVert, &maxLengthVert, &errorLogVert[0]);
		if (errorLogVert.size() > 0)
			std::cout << errorLogVert.data();

		std::cout << "check shader fragment: " << isCompiledFrag << std::endl;
		GLint maxLengthFrag = 0;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLengthFrag);
		std::cout << "maxLengthFrag: " << maxLengthFrag << std::endl;
		std::vector<GLchar> errorLogFrag(maxLengthFrag);
		glGetShaderInfoLog(fragment_shader, maxLengthFrag, &maxLengthFrag, &errorLogFrag[0]);
		if (errorLogFrag.size() > 0)
			std::cout << errorLogFrag.data();
	}

    GLuint mvp_location = glGetUniformLocation(program, "MVP");
    GLuint vcol_location = glGetAttribLocation(program, "vCol");
    GLuint vpos_location = glGetAttribLocation(program, "vPos");
    std::cout << mvp_location << std::endl;
    std::cout << vcol_location << std::endl;
    std::cout << vpos_location << std::endl;

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 2));

    double prevTime = glfwGetTime();
    uint32_t frames = 0;
    while (!glfwWindowShouldClose(window))
    {        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glm::mat4 m = glm::rotate(glm::mat4(1.0f), (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 p = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glm::mat4 mvp = p*m;

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetTime() - prevTime > 1.0) {
            std::cout << "Frames per second: " << frames << std::endl;
            prevTime = glfwGetTime();
            frames = 0;
        }
        frames++;
    }

    glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
