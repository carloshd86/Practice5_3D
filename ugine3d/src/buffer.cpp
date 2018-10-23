#include "buffer.h"
#include "shader.h"
#include "vertex.h"

BufferPtr Buffer::create(const VertexVec& vertices, const IndexVec& indices) {
	std::shared_ptr<Buffer> p(new Buffer(vertices, indices), [](Buffer* p) {
		delete p;
	});
	return p;
}

Buffer::Buffer(const VertexVec& vertices, const IndexVec& indices) {
	glGenBuffers(2, m_ids.data());
	glBindBuffer(GL_ARRAY_BUFFER, m_ids[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ids[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
	m_numIndices = indices.size();
}

Buffer::~Buffer() {
	glDeleteBuffers(2, m_ids.data());
}

void Buffer::draw(const Shader& shader) const {
	glBindBuffer(GL_ARRAY_BUFFER, m_ids[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ids[1]);
	shader.setupAttribs();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_numIndices), GL_UNSIGNED_SHORT, nullptr);
}
