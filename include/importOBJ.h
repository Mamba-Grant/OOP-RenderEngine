
// functions necessary for importing a file with the .obj extension
// allows the user to load a model from external software\
//
// much of the logic for this code came from the guide linked below:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#pragma once

#include "datatypes/mesh.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

// global
std::vector<glm::vec3> tmp_vertices;
std::vector<glm::vec2> tmp_UVs;
std::vector<glm::vec3> tmp_normals;
std::vector< GLuint > tmp_vertexIndices, tmp_uvIndices, tmp_normalIndices;

void import(char* filename, mesh* mesh) {

  mesh->name = filename;

  // open file 
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("Image could not be opened\n"); 
    return;
  }

  printf("\nLoading: %s:\n\n",mesh->name.c_str());
  
  // read file
  for (;;) {
    char* lineHeader;
    // read the first word of the line
    int res = fscanf(file, "%s ", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. Quit the loop.
    if ( strcmp( lineHeader, "v" ) == 0 ){
        glm::vec3 vertexCoord;
        fscanf(file, "%f %f %f\n", &vertexCoord.x, &vertexCoord.y, &vertexCoord.z );
      tmp_vertices.push_back(vertexCoord);
      }
    else if ( strcmp( lineHeader, "vt" ) == 0 ){
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        tmp_UVs.push_back(uv);
      }
    else if ( strcmp( lineHeader, "vn" ) == 0 ){
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        tmp_normals.push_back(normal);
      }
    else if ( strcmp( lineHeader, "f" ) == 0 ){
      unsigned int test;
      static GLuint vertexIndex[3], uvIndex[3], normalIndex[3];

      fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

      mesh->vertexIndices.push_back(vertexIndex[0]);
      mesh->vertexIndices.push_back(vertexIndex[1]);
      mesh->vertexIndices.push_back(vertexIndex[2]);
      mesh->uvIndices    .push_back(uvIndex[0]);
      mesh->uvIndices    .push_back(uvIndex[1]);
      mesh->uvIndices    .push_back(uvIndex[2]);
      mesh->normalIndices.push_back(normalIndex[0]);
      mesh->normalIndices.push_back(normalIndex[1]);
      mesh->normalIndices.push_back(normalIndex[2]); 
    }
  }
  printf("Finished Loading: %s:\n",mesh->name.c_str());

  // we can reserve space for vertices as we already know the number that will be inserted
  mesh->vertices.reserve(mesh->vertexIndices.size());

  for( unsigned int i=0; i<mesh->vertexIndices.size(); i++ ) {
    unsigned int vertexIndex = mesh->vertexIndices[i];
    std::cout<<glm::to_string(tmp_vertices[vertexIndex-1])<<std::endl;
    vertex* fileVertex = new vertex{tmp_vertices[ vertexIndex-1 ]};
    mesh->vertices.push_back(*fileVertex);
  }
  
  return;
}