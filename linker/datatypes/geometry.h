#pragma once
#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include <vector>

// simple vertex object which holds
// a position, color, texcoord, and normal vector
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


// simple mesh object which holds 
// a name, vertex list, and index list
//
// faces/polygons are an abstract
// part of this - use of indices and verticies
// to calculate faces
class mesh {
  public:
		// Mesh Name
	std::string name;
		// Vertex List
  std::vector<vertex> vertices;
		// Index List
	std::vector<unsigned int> indices;

  std::vector<vertex> polygroups;

  mesh() {}
  mesh(std::vector<vertex> v, std::vector<unsigned int> ind)
    	: vertices(v), indices(ind) {}
};