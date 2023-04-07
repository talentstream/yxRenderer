#include "rasterizer.h"
#include<iostream>

Rasterizer::Rasterizer(int w, int h) :width(w), height(h)
{
	frame_buffer.resize(w * h);
	depth_buffer.resize(w * h);
}

pos_buffer_id Rasterizer::LoadPositions(const std::vector<Eigen::Vector3f>& positions)
{
	auto id = GetNextId();
	pos_buffer.emplace(id, positions);

	return { id };
}

index_buffer_id Rasterizer::LoadIndices(const std::vector<Eigen::Vector3f>& indices)
{
	auto id = GetNextId();
	index_buffer.emplace(id, indices);

	return { id };
}

void Rasterizer::SetPixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color)
{
	if (point.x() < 0 || point.x() >= width || point.y() < 0 || point.y() >= height) return;
	auto ind = GetIndex(point.x(), point.y());
	frame_buffer[ind] = color;
}

auto ToVec4(const Eigen::Vector3f& v, float w = 1.0f)
{
	return Eigen::Vector4f(v.x(), v.y(), v.z(),w);
}
void Rasterizer::Draw(pos_buffer_id pos_buf, index_buffer_id index_buf, Primitive primitive)
{
	auto& buf = pos_buffer[pos_buf.pos_id];
	auto& ind = index_buffer[index_buf.index_id];

	std::cout <<"# buf_size : " << buf.size() << std::endl;
	std::cout << "# ind_size : " << ind.size() << std::endl;

	float f1 = (100 - 0.1) / 2.0;
	float f2 = (100 + 0.1) / 2.0;

	Eigen::Matrix4f mvp = projection * view  * model;

	for (auto& i : ind)
	{
		Triangle t;

		Eigen::Vector4f v[] = {
			mvp * ToVec4(buf[i[0]],1.0f),
			mvp * ToVec4(buf[i[1]],1.0f),
			mvp * ToVec4(buf[i[2]],1.0f)
		};

		for (auto& vec : v)
		{
			// std::cout <<"#before2 " << vec.x() << " " << vec.y() << " " <<  vec.z() << std::endl;
			vec /= vec.w();

			vec.x() = 0.5 * width * (vec.x() + 1.0);
			vec.y() = 0.5 * height * (vec.y() + 1.0);
			vec.z() = vec.z() * f1 + f2;
			// std::cout << "#after2" << vec.x() << " " << vec.y() << " " << vec.z() << std::endl;
		}

		for (int i = 0; i < 3; ++i)
		{
			t.SetVertex(i, v[i].head<3>());
			t.SetVertex(i, v[i].head<3>());
			t.SetVertex(i, v[i].head<3>());
		}

		t.SetColor(0, 255.0, 0.0, 0.0);
		t.SetColor(1, 0.0, 255.0, 0.0);
		t.SetColor(2, 0.0, 0.0, 255.0);

		DrawTriangle(t);
	}
}

void Rasterizer::Clear(Buffers buffer)
{
	if ((buffer & Buffers::Color) == Buffers::Color)
	{
		std::fill(frame_buffer.begin(), frame_buffer.end(), Eigen::Vector3f(0));
	}
	if ((buffer & Buffers::Depth) == Buffers::Depth)
	{
		std::fill(depth_buffer.begin(), depth_buffer.end(), std::numeric_limits<float>::infinity());
	}
}

void Rasterizer::DrawLine(Eigen::Vector3f begin, Eigen::Vector3f end)
{
	int x0 = begin.x(), y0 = begin.y();
	int x1 = end.x(), y1 = end.y();
	std::cout << x0 << " " << y0 << " " << x1 << " " << y1 << std::endl;

	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;

	int err = (dx > dy ? dx : -dy) / 2;

	while (x0 != x1 || y0 != y1) {
		SetPixel(Eigen::Vector3f(x0, y0, 1.0f), Eigen::Vector3f(255, 255, 255));
		int e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void Rasterizer::DrawTriangle(const Triangle& tri)
{
	DrawLine(tri.vertex[2], tri.vertex[0]);
	DrawLine(tri.vertex[2], tri.vertex[1]);
	DrawLine(tri.vertex[1], tri.vertex[0]);
}
