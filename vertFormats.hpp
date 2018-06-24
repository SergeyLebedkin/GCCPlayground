#pragma once

// vertex with position and color
struct VFCoordColor
{
    float x, y, z;
    float r, g, b;
};

// vertex with position, color and 2d tex coords
struct VFCoordColorTex2d
{
    float x, y, z;
    float r, g, b;
    float u, v;
};