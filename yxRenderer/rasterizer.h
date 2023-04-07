#pragma once

#include "triangle.h"

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


	pos_buffer_id LoadPositions(const std::vector<glm::vec3>& positions);
	index_buffer_id LoadIndices(const std::vector<glm::vec3>& indices);

	void SetModel(const glm::mat4& m) { model = m; }
	void SetView(const glm::mat4& v) { view = v; }
	void SetProjection(const glm::mat4& p) { projection = p; }
	
	void SetPixel(const glm::vec3& point, const glm::vec3& color);

	void Draw(pos_buffer_id pos_buffer,index_buffer_id index_buffer, Primitive primitive);

	void Clear(Buffers buffer);

	std::vector<glm::vec3>& GetFrameBuffer() { return frame_buffer; }

	~Rasterizer(){}

private:
	void DrawLine(glm::vec3 begin, glm::vec3 end);
	void DrawTriangle(const Triangle& tri);
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	std::map<int, std::vector<glm::vec3>> pos_buffer;
	std::map<int, std::vector<glm::vec3>> index_buffer;

	std::vector<glm::vec3> frame_buffer;
	std::vector<float> depth_buffer;

	int GetIndex(int x, int y) { return (x + width * (height - y)); }
	int width, height;

	int next_id = 0;
	int GetNextId() { return next_id++; }
};