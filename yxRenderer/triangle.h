#pragma once
#ifndef  RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

#include<glm/glm.hpp>
#include<Eigen/Dense>

class Triangle
{
public:
	Eigen::Vector3f vertex[3];
	Eigen::Vector3f color[3];
	Eigen::Vector2f tex_coords[3];
	Eigen::Vector3f normal[3];

	Triangle();

	void SetVertex(int index, Eigen::Vector3f vert);
	void SetColor(int index, float r, float g, float b);
	void SetTexCoords(int index, float u, float v);
	void SetNormal(int index, Eigen::Vector3f norm);
	Eigen::Vector3f GetColor() const { return color[0] * 255; }
};
#endif // ! RASTERIZER_TRIANGLE_H
