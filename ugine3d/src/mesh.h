#pragma once

#include "buffer.h"
#include "common.h"
#include "material.h"
#include <utility>

class Mesh;
typedef std::shared_ptr<Mesh> MeshPtr;

class Mesh {
public:
	static MeshPtr create();
	static MeshPtr load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);
	void addBuffer(const BufferPtr& buffer, const Material& material);
	size_t getNumBuffers() const;
	const BufferPtr& getBuffer(size_t index) const;
	BufferPtr& getBuffer(size_t index);
	void draw();
	const Material& getMaterial(size_t index) const;
	Material& getMaterial(size_t index);
protected:
	Mesh() {}
	~Mesh() {}
private:
	typedef std::pair<BufferPtr, Material> MeshPair;
	std::vector<MeshPair> m_buffers;
};