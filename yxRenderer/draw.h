#ifndef DRAW_H
#define DRAW_H

#include "tgaimage.h"

#include<glm/glm.hpp>

void DrawPoint(int x0, int y0, TGAImage& image, TGAColor color);
void DrawLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
void DrawLine(glm::vec2 p0, glm::vec2 p1, TGAImage& image, TGAColor color);
void DrawTriangle(glm::vec2 t0, glm::vec2 t1, glm::vec2 t2, TGAImage& image, TGAColor color);
void DrawTriangle(glm::vec3 t0, glm::vec3 t1, glm::vec3 t2, TGAImage& image, TGAColor color, float* zbuffer);

#endif // !DRAW_H


