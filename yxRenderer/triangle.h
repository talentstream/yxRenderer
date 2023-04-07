#pragma once
#ifndef  RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

#include<glm/glm.hpp>

class Triangle
{
public:
	glm::vec3 vertex[3];
	glm::vec3 color[3];
	glm::vec2 tex_coords[3];
	glm::vec3 normal[3];

	Triangle();

	void SetVertex(int index, glm::vec3 vert);
	void SetColor(int index, float r, float g, float b);
	void SetTexCoords(int index, float u, float v);
	void SetNormal(int index, glm::vec3 norm);
	glm::vec3 GetColor() const { return glm::vec3(255.0 * color[0].x, 255.0 * color[0].y, 255.0 * color[0].z); }
};
#endif // ! RASTERIZER_TRIANGLE_H
