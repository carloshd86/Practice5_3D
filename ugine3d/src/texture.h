#pragma once

#include "common.h"


class Texture {

public:
	static std::shared_ptr<Texture>	load(const char* filename);
	uint32_t					    getId()   const;
	const glm::ivec2&				getSize() const;
	void						    bind()    const;

protected:
	Texture();
	~Texture();

private:
	uint32_t   mTexId;
	glm::ivec2 mSize;
};