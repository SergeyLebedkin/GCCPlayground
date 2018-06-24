#pragma once

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

void output_all_shaders();