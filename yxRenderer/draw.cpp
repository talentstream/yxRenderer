#include "draw.h"
#include<tuple>

bool IsInsideTriangle(float x, float y, glm::vec2 t0, glm::vec2 t1, glm::vec2 t2);
std::tuple<float, float, float> computeBarycentric2D(float x, float y, glm::vec2 t0, glm::vec2 t1, glm::vec2 t2);


void DrawPoint(int x0, int y0, TGAImage& image, TGAColor color)
{
	image.set(x0, y0, color);
}

void DrawLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	// 在这里我们绘制Bresenham直线
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;

	int err = (dx > dy ? dx : -dy) / 2;

	while (x0 != x1 || y0 != y1) {
		image.set(x0, y0, color);
		int e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void DrawLine(glm::vec2 p0, glm::vec2 p1, TGAImage& image, TGAColor color)
{
	int x0 = p0.x, y0 = p0.y;
	int x1 = p1.x, y1 = p1.y;

	DrawLine(x0, y0, x1, y1, image, color);
}

void DrawTriangleWireFrame(glm::vec2 t0, glm::vec2 t1, glm::vec2 t2, TGAImage& image, TGAColor color)
{
	DrawLine(t0, t1, image, color);
	DrawLine(t1, t2, image, color);
	DrawLine(t2, t0, image, color);
}

void DrawTriangle(glm::vec2 t0, glm::vec2 t1, glm::vec2 t2, TGAImage& image, TGAColor color)
{
	float min_x = std::min(std::min(t0.x, t1.x), t2.x);
	float max_x = std::max(std::max(t0.x, t1.x), t2.x);
	float min_y = std::min(std::min(t0.y, t1.y), t2.y);
	float max_y = std::max(std::max(t0.y, t1.y), t2.y);

	/*for (int x = min_x; x <= max_x + 1; x++)
	{
		for (int y = min_y; y <= max_y + 1; y++)
		{
			if (!IsInsideTriangle(x, y, t0, t1, t2))
				continue;
			auto [alpha, beta, gamma] = computeBarycentric2D(x, y, t0, t1, t2);
			if (alpha < 0 || beta < 0 || gamma < 0)
				continue;
			image.set(x, y, color);
		}
	}*/
}

void DrawTriangle(glm::vec3 t0, glm::vec3 t1, glm::vec3 t2, TGAImage& image, TGAColor color, float* zbuffer)
{
	float min_x = std::min(std::min(t0.x, t1.x), t2.x);
	float max_x = std::max(std::max(t0.x, t1.x), t2.x);
	float min_y = std::min(std::min(t0.y, t1.y), t2.y);
	float max_y = std::max(std::max(t0.y, t1.y), t2.y);

	/*for (int x = min_x; x <= max_x + 1; x++)
	{
		for (int y = min_y; y <= max_y + 1; y++)
		{
			if (!IsInsideTriangle(x, y, t0, t1, t2)) continue;
			auto [alpha, beta, gamma] = computeBarycentric2D(x, y, t0, t1, t2);
			if (alpha < 0 || beta < 0 || gamma < 0) continue;
			float z = alpha * t0.z + beta * t1.z + gamma * t2.z;
			if (zbuffer[x + y * image.get_width()] < z)
			{
				zbuffer[x + y * image.get_width()] = z;
				image.set(x, y, color);
			}
		}
	}*/

}
bool IsInsideTriangle(float x, float y, glm::vec2 t0, glm::vec2 t1, glm::vec2 t2)
{
	glm::vec3 p(x, y, 1), v0(t0, 1), v1(t1, 1), v2(t2, 1);
	glm::vec3 f0 = glm::cross(v1, v0);
	glm::vec3 f1 = glm::cross(v2, v1);
	glm::vec3 f2 = glm::cross(v0, v2);
	if (glm::dot(f0, p) * glm::dot(f0, v2) > 0 && glm::dot(f1, p) * glm::dot(f1, v0) > 0 && glm::dot(f2, p) * glm::dot(f2, v1) > 0)
		return true;
	return false;
}

std::tuple<float, float, float> computeBarycentric2D(float x, float y, glm::vec2 t0, glm::vec2 t1, glm::vec2 t2)
{
	float alpha = (x * (t1.y - t2.y) + (t2.x - t1.x) * y + t1.x * t2.y - t2.x * t1.y) / (t0.x * (t1.y - t2.y) + (t2.x - t1.x) * t0.y + t1.x * t2.y - t2.x * t1.y);
	float beta = (x * (t2.y - t0.y) + (t0.x - t2.x) * y + t2.x * t0.y - t0.x * t2.y) / (t1.x * (t2.y - t0.y) + (t0.x - t2.x) * t1.y + t2.x * t0.y - t0.x * t2.y);
	float gamma = (x * (t0.y - t1.y) + (t1.x - t0.x) * y + t0.x * t1.y - t1.x * t0.y) / (t2.x * (t0.y - t1.y) + (t1.x - t0.x) * t2.y + t0.x * t1.y - t1.x * t0.y);
	return { alpha,beta,gamma };
}