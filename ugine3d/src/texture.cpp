#include "texture.h"
#include <stb_image.h>


std::shared_ptr<Texture> Texture::load(const char* filename) {
	std::shared_ptr<Texture> p(new Texture(), [](Texture* p) {
		delete p;
	});

	// Cargamos pixeles con STB Image
	stbi_set_flip_vertically_on_load(true);
	uint8_t* buffer = stbi_load(filename, &p->mSize.x, &p->mSize.y, nullptr, 4);
	if (!buffer) return nullptr;

	// Generamos la copia en memoria de video
	glGenTextures(1, &p->mTexId);
	glBindTexture(GL_TEXTURE_2D, p->mTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p->mSize.x, p->mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Borramos buffer de STB Image
	stbi_image_free(buffer);

	return p;
}

/******************/

Texture::Texture() :
	mSize(0, 0),
	mTexId(0) {}

/******************/

Texture::~Texture() {
	if (mTexId) glDeleteTextures(1, &mTexId);
}

/******************/

uint32_t Texture::getId() const {
	return mTexId;
}

/******************/

const glm::ivec2& Texture::getSize() const {
	return mSize;
}

/******************/

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, mTexId);
}