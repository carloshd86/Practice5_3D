#pragma once

#include "common.h"
#include <array>

class Buffer;
class Shader;

typedef std::shared_ptr<Buffer> BufferPtr;

class Buffer {
public:
	static BufferPtr create(const VertexVec& vertices, const IndexVec& indices);

	void draw(const Shader& shader) const;
protected:
	Buffer(const VertexVec& vertices, const IndexVec& indices);
	~Buffer();
private:
	std::array<uint32_t, 2>	m_ids;
	size_t					m_numIndices;
};