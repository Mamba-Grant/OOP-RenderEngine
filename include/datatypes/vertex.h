#pragma once
#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include <vector>

class vertex {
  public:
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texcoord;
  glm::vec3 normal;

  // constructors
  vertex() {}
  vertex (glm::vec3 pos)
    : position(pos) {}
  vertex(glm::vec3 pos, glm::vec3 col, glm::vec2 UV, glm::vec3 norm)
    : position(pos), color(col), texcoord(UV), normal(norm) {}
};