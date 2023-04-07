#include "triangle.h"

Triangle::Triangle()
{
	vertex[0] << Eigen::Vector3f(0, 0, 0);
	vertex[1] << Eigen::Vector3f(0, 0, 0);
	vertex[2] << Eigen::Vector3f(0, 0, 0);

	color[0] << Eigen::Vector3f(0, 0, 0);
	color[1] << Eigen::Vector3f(0, 0, 0);
	color[2] << Eigen::Vector3f(0, 0, 0);

	tex_coords[0] << Eigen::Vector2f(0, 0);
	tex_coords[1] << Eigen::Vector2f(0, 0);
	tex_coords[2] << Eigen::Vector2f(0, 0);
}

void Triangle::SetVertex(int index, Eigen::Vector3f vert)
{
	vertex[index] = vert;
}

void Triangle::SetNormal(int index, Eigen::Vector3f norm)
{
	normal[index] = norm;
}
void Triangle::SetColor(int index, float r, float g, float b)
{
	if ((r < 0 || r>255) || (g < 0 || g>255) || (b < 0 || b>255))
	{
		fprintf(stderr, "ERROR! Invalid color values");
		fflush(stderr);
		exit(-1);
	}

	color[index] = Eigen::Vector3f((float)r / 255.0, (float)g / 255.0, (float)b / 255.0);
}

void Triangle::SetTexCoords(int index, float u, float v)
{
	tex_coords[index] = Eigen::Vector2f(u, v);
}


