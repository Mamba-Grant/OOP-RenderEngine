//#include "freeglut-3.2.1/include/GL/freeglut.h"

#include "../linker/glm/glm.hpp"
#include "../linker/glm/gtx/string_cast.hpp"
#include "../linker/importOBJ.h"
#include "../linker/datatypes/generic_class.h"

#include <iostream>

int main() {

  mesh* cube = new mesh;
  import((char*)"OBJs/cube.obj", cube);

  mesh* suzanne = new mesh;
  import((char*)"OBJs/suzanne.obj", cube);

  generic_container* obj1 = new generic_container{"obj1", cube, NULL};
  generic_container* obj2 = new generic_container {"obj2", suzanne, obj1};

  std::cout<<obj2->parent_ptr->name;
  
  return 0;
}

// OpenGL thingy: 
//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);