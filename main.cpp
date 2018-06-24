#include <iostream>

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

// vertex shader source code
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

// fragment shader source code
static const char* fragment_shader_text = R"(
precision lowp float;
varying vec3 color;
void main()
{
    gl_FragColor = vec4(color, 1.0);
}
)";

// key callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// main
int main(int argc, char ** argv)
{
    // set error handling
	glfwSetErrorCallback([](int error, const char* description){
        std::cout << "Error: " << description << std::endl;
    });

    // init glfw
	if (!glfwInit())
		exit(EXIT_FAILURE);

    // select OpenGL version
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // create glfw window
	GLFWwindow* window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

    // make context current
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

    // print opengl caps
	output_opengl_caps();

    // create VBO
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

    // check shaders statuses
    if (!shader_status_check(vertex_shader))
        std::cout << "vertex shader error!";
    if (!shader_status_check(fragment_shader))
        std::cout << "fragment shader error!";

    // get attributes and uniforms location
    GLuint mvp_location = glGetUniformLocation(program, "MVP");
    GLuint vcol_location = glGetAttribLocation(program, "vCol");
    GLuint vpos_location = glGetAttribLocation(program, "vPos");

    // set attribs arrays
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 2));

    // main cicle
    double prevTime = glfwGetTime();
    uint32_t frames = 0;
    while (!glfwWindowShouldClose(window))
    {   
        // get window parameters
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);

        // create matrixes
        float ratio = width / (float) height;
        glm::mat4 m = glm::rotate(glm::mat4(1.0f), (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 p = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glm::mat4 mvp = p*m;

        // init draw buffer
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // draw, using shader
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap baffer
        glfwSwapBuffers(window);
        glfwPollEvents();

        // FPS
        double diffTime = glfwGetTime() - prevTime;
        if (diffTime > 1.0) 
        {
            std::cout << "Time: " << diffTime << "; ";
            std::cout << "Frames: " << frames << "; ";
            std::cout << "FPS: " << frames/diffTime;
            std::cout << std::endl;
            prevTime = glfwGetTime();
            frames = 0;
        }
        frames++;
    }

    // destroy window and exit
    glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
