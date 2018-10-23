#pragma once

#include <GL/glew.h>
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/random.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"
#include "../lib/glm/gtx/string_cast.hpp"
#include "vertex.h"
#include <forward_list>
#include <memory>
#include <vector>

typedef std::vector<Vertex>		VertexVec;
typedef std::vector<uint16_t>	IndexVec;