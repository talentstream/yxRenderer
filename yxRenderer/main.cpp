#include <vector>
#include <cmath>
#include <iostream>
#include "tgaimage.h"
#include "draw.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

const static int width = 800;
const static int height = 800;

const static float PI = 3.1415927f;

void test_drawline(TGAImage& image, TGAColor color);
void test_drawtriangle(TGAImage& image, TGAColor color);
void test_z_buffer(TGAImage& image, float* zbuffer);

glm::mat4 GetViewMatrix(glm::vec3 eye_pos)
{
	glm::mat4 view = glm::mat4(1.0f);

	glm::mat4 translate(1, 0, 0, -eye_pos.x,
		0, 1, 0, -eye_pos.y,
		0, 0, 1, -eye_pos.z,
		0, 0, 0, 1);

	view = translate * view;

	return view;
}
glm::mat4 GetModelMatrix(float angle)
{
	angle = angle * PI / 180.0f;

	glm::mat4 rotation(cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 translate = glm::mat4(1.0f);

	return translate * rotation * scale;
}
glm::mat4 GetProjectionMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar)
{

	float eye_angle = eye_fov * acos(-1) / 180;

	float top = tan(eye_angle / 2.0f) * zNear;
	float right = top * aspect_ratio;

	glm::mat4 projection(zNear / zFar, 0, 0, 0,
		0, zNear / top, 0, 0,
		0, 0, (zNear + zFar) / (zNear - zFar), (2 * zNear * zFar) / (zNear - zFar),
		0, 0, -1, 0);

	return projection;
}
int main(int argc, char** argv) {
	TGAImage image(width, height, TGAImage::RGB);

	// test_drawline(image, green);
	// test_drawtriangle(image, green);
	float* zbuffer = new float[width * height];

	for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max());


	test_z_buffer(image, zbuffer);
	image.flip_vertically();
	image.write_tga_file("output.tga");

	return 0;
}


void test_drawline(TGAImage& image, TGAColor color)
{
	float cx = width * 0.5f - 0.5f, cy = height * 0.5f - 0.5f;
	for (int j = 0; j < 5; j++) {
		float r1 = fminf(width, height) * (j + 0.5f) * 0.085f;
		float r2 = fminf(width, height) * (j + 1.5f) * 0.085f;
		float t = j * 3.14 / 64.0f;
		for (int i = 1; i <= 64; i++, t += 2.0f * 3.14 / 64.0f) {
			float ct = cosf(t), st = sinf(t);
			DrawLine((int)(cx + r1 * ct), (int)(cy - r1 * st), (int)(cx + r2 * ct), (int)(cy - r2 * st), image, color);
		}
	}
}

void test_drawtriangle(TGAImage& image, TGAColor color)
{
	DrawTriangle(glm::vec2(10, 10), glm::vec2(100, 30), glm::vec2(190, 160), image, color);
}

void test_z_buffer(TGAImage& image, float* zbuffer)
{
	DrawTriangle(glm::vec3(400, 200, -2), glm::vec3(200, 400, -2), glm::vec3(0, 200, -2), image, TGAColor(217, 238, 185, 255), zbuffer);
	DrawTriangle(glm::vec3(550, 100, -5), glm::vec3(450, 350, -5), glm::vec3(100, 250, -5), image, TGAColor(185, 217, 238, 255), zbuffer);
}
