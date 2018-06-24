#include "shaders.hpp"
#include <iostream>

// output all shaders
// this function needs to avoid "defined but not used" warning
void output_all_shaders()
{
	std::cout << "vertex_shader_text:" << std::endl << vertex_shader_text << std::endl;
	std::cout << "fragment_shader_text:" << std::endl << fragment_shader_text << std::endl;
}