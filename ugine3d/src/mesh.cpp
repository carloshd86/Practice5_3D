#include "mesh.h"
#include "state.h"
#include "pugixml.hpp"
#include "util.h"
#include "texture.h"
#include <iostream>

MeshPtr Mesh::create() {
	std::shared_ptr<Mesh> p(new Mesh, [](Mesh* p) {
		delete p;
	});
	return p;
}

MeshPtr Mesh::load(const char* filename, const std::shared_ptr<Shader>& shader) {		
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename);

	if (result) {

		std::shared_ptr<Mesh> p(new Mesh(), [](Mesh* p) {
			delete p;
		});

		std::string dataPath = extractPath(filename);
		pugi::xml_node meshNode = doc.child("mesh");
		pugi::xml_node buffersNode = meshNode.child("buffers");

		for (pugi::xml_node bufferNode = buffersNode.child("buffer"); bufferNode; bufferNode = bufferNode.next_sibling("buffer")) {
			std::string texPath = dataPath + bufferNode.child("material").child("texture").text().as_string();
			std::shared_ptr<Texture> tex = Texture::load(texPath.c_str());
			Material material(tex, shader);

			pugi::xml_node indicesNode = bufferNode.child("indices");
			std::vector<uint16_t> indices = splitString<uint16_t>(indicesNode.text().as_string(), ',');

			pugi::xml_node coordsNode = bufferNode.child("coords");
			std::vector<float> coords = splitString<float>(coordsNode.text().as_string(), ',');

			pugi::xml_node texCoordsNode = bufferNode.child("texcoords");
			std::vector<float> texCoords = splitString<float>(texCoordsNode.text().as_string(), ',');

			std::vector<Vertex> vertices;
			for (int i = 0, j = 0; i < coords.size(), j < texCoords.size(); i += 3, j += 2) {
				vertices.push_back(Vertex(glm::vec3(coords[i], coords[i+1],  coords[i+2]), glm::vec3(1, 1, 1), glm::vec2(texCoords[j], texCoords[j+1])));
			}

			p->addBuffer(Buffer::create(vertices, indices), material);
		}

		return p;
	} else {
		// No se ha podido cargar
		std::cout << result.description() << std::endl;
		return nullptr;
	}
}

void Mesh::addBuffer(const BufferPtr& buffer, const Material& material) {
	m_buffers.push_back(std::make_pair(buffer, material));
}

size_t Mesh::getNumBuffers() const {
	return m_buffers.size();
}

const BufferPtr& Mesh::getBuffer(size_t index) const {
	return m_buffers[index].first;
}

BufferPtr& Mesh::getBuffer(size_t index) {
	return m_buffers[index].first;
}

void Mesh::draw() {
	for ( MeshPair& mp : m_buffers ) {
		BufferPtr& buffer = mp.first;
		Material& material = mp.second;
		material.prepare();
		buffer->draw(*material.getShader());
	}
}

const Material& Mesh::getMaterial(size_t index) const {
	return const_cast<const Material&>(m_buffers[index].second);
}

Material& Mesh::getMaterial(size_t index) {
	return m_buffers[index].second;
}