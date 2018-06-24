#pragma once

#include <GLFW/glfw3.h>

// vertex shader source code
static const GLchar *vertex_shader_text = R"(
uniform mat4 uMVP;
attribute vec3 aPosition;
attribute vec3 aColor;
varying vec3 vColor;
void main()
{
    gl_Position = uMVP * vec4(aPosition, 1.0);
    vColor = aColor;
}
)";

// fragment shader source code
static const GLchar *fragment_shader_text = R"(
precision lowp float;
varying vec3 vColor;
void main()
{
    gl_FragColor = vec4(vColor, 1.0);
}
)";

void output_all_shaders();