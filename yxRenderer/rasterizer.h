#pragma once

#include "triangle.h"

#include<Eigen/Eigen>
#include<glm/glm.hpp>
#include<map>
#include<vector>

enum class Buffers
{
	Color = 1,
	Depth = 2
};

inline Buffers operator|(Buffers a, Buffers b)
{
	return static_cast<Buffers>(static_cast<int>(a) | static_cast<int>(b));
}

inline Buffers operator&(Buffers a, Buffers b)
{
	return static_cast<Buffers>(static_cast<int>(a) & static_cast<int>(b));
}

enum class Primitive
{
	Line,
	Triangle
};

struct pos_buffer_id
{
	int pos_id = 0;
};

struct index_buffer_id
{
	int index_id = 0;
};

class Rasterizer
{
public:
	Rasterizer(int w, int h);


	pos_buffer_id LoadPositions(const std::vector<Eigen::Vector3f>& positions);
	index_buffer_id LoadIndices(const std::vector<Eigen::Vector3f>& indices);

	void SetModel(const Eigen::Matrix4f& m) { model = m; }
	void SetView(const Eigen::Matrix4f& v) { view = v; }
	void SetProjection(const Eigen::Matrix4f& p) { projection = p; }
	
	void SetPixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color);

	void Draw(pos_buffer_id pos_buffer,index_buffer_id index_buffer, Primitive primitive);

	void Clear(Buffers buffer);

	std::vector<Eigen::Vector3f>& GetFrameBuffer() { return frame_buffer; }

	~Rasterizer(){}

private:
	void DrawLine(Eigen::Vector3f begin, Eigen::Vector3f end);
	void DrawTriangle(const Triangle& tri);
private:
	Eigen::Matrix4f model;
	Eigen::Matrix4f view;
	Eigen::Matrix4f projection;

	std::map<int, std::vector<Eigen::Vector3f>> pos_buffer;
	std::map<int, std::vector<Eigen::Vector3f>> index_buffer;

	std::vector<Eigen::Vector3f> frame_buffer;
	std::vector<float> depth_buffer;

	int GetIndex(int x, int y) { return (x + width * (height - y)); }
	int width, height;

	int next_id = 0;
	int GetNextId() { return next_id++; }
};