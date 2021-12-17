#pragma once
#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include "vertex.h"
#include <vector>

class mesh {
  public:
	std::string name;
  std::vector<vertex> vertices;
  std::vector<GLuint> vertexIndices;
  std::vector<GLuint> uvIndices;
  std::vector<GLuint> normalIndices;
};