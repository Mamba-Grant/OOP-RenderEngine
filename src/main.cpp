// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#include "../linker/glm/glm.hpp"
#include "../linker/glm/gtx/string_cast.hpp"
#include "../linker/geometry.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>

// global
std::vector<glm::vec2> tmp_UVs;
std::vector<glm::vec3> tmp_normal;
std::vector<unsigned int> tmp_vertexIndices;
std::vector<unsigned int> tmp_uvIndices;
std::vector<unsigned int> tmp_normalIndices;

// enum and hash functions for more concise
// switch statement instead of if/elses 
enum string_code {
  ev,     // vertex position
  ef,     // face position
  evt,    // vertex texture coordinate
  evn,    // vertex normal
  ed      // default hash
};

string_code hash (std::string const& inString) {
    if (inString == "v") return ev;
    if (inString == "vn") return evn;
    if (inString == "vt") return evt;
    if (inString == "f") return ef;
    else return ed;
}

void importOBJ(char* filename, mesh* mesh) {

  // open file 
  FILE* file = fopen (filename, "r");
  if (!file) {
    printf("Image could not be opened\n"); 
    return;
  }

  // read file
  for (;;) {
    char* lineHeader;
    // read the first word of the line
    int res = fscanf(file, "%s ", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. Quit the loop.
    /* honestly just need to change
    this to a if/else if chain, hashing
    is a redundant step */
    switch (hash(lineHeader)) {
      case ev: {
        glm::vec3 vertexCoord;
        fscanf(file, "%f %f %f\n", &vertexCoord.x, &vertexCoord.y, &vertexCoord.z );
        
        vertex* fileVertex = new vertex{vertexCoord};
        mesh->vertices.push_back(*fileVertex);
        break;
      }
      case evt: {
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        tmp_UVs.push_back(uv);
        break;
      }
      case evn: {
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        tmp_normal.push_back(normal);
        break;
      }
      case ef: {
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[300], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    
        if (matches != 9){
          printf("File can't be read by this parser");
          return;
        }
        tmp_vertexIndices.push_back(vertexIndex[0]);
        tmp_vertexIndices.push_back(vertexIndex[1]);
        tmp_vertexIndices.push_back(vertexIndex[2]);
        tmp_uvIndices    .push_back(uvIndex[0]);
        tmp_uvIndices    .push_back(uvIndex[1]);
        tmp_uvIndices    .push_back(uvIndex[2]);
        tmp_normalIndices.push_back(normalIndex[0]);
        tmp_normalIndices.push_back(normalIndex[1]);
        tmp_normalIndices.push_back(normalIndex[2]);

        break; 
      }     
    }
  }
}

int main() {

  vertex* a = new vertex{glm::vec3(1,1,1)};
  //std::cout<<glm::to_string(a->position)<<std::endl;

  mesh* testMesh = new mesh;
  importOBJ((char*)"testmodel.obj", testMesh);

  for (auto i : testMesh->vertices) {
    std::cout<<glm::to_string(i.position)<<std::endl;
  }
  
  return 0;
}