
// functions necessary for importing a file with the .obj extension
// allows the user to load a model from external software\
//
// much of the logic for this code came from the guide linked below:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#pragma once

#include "datatypes/geometry.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

// global
std::vector<glm::vec3> tmp_vertices;
std::vector<glm::vec2> tmp_UVs;
std::vector<glm::vec3> tmp_normals;
std::vector< unsigned int > tmp_vertexIndices, tmp_uvIndices, tmp_normalIndices;

void import(char* filename, mesh* mesh) {

  mesh->name = filename;

  // open file 
  FILE* file = fopen(filename, "r");
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
    if ( strcmp( lineHeader, "v" ) == 0 ){
        glm::vec3 vertexCoord;
        fscanf(file, "%f %f %f\n", &vertexCoord.x, &vertexCoord.y, &vertexCoord.z );

      vertex* fileVertex = new vertex{vertexCoord};
      mesh->vertices.push_back(*fileVertex);

      //tmp_vertices.push_back(vertexCoord);
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
      static unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

      fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

      tmp_vertexIndices.push_back(vertexIndex[0]);
      tmp_vertexIndices.push_back(vertexIndex[1]);
      tmp_vertexIndices.push_back(vertexIndex[2]);
      tmp_uvIndices    .push_back(uvIndex[0]);
      tmp_uvIndices    .push_back(uvIndex[1]);
      tmp_uvIndices    .push_back(uvIndex[2]);
      tmp_normalIndices.push_back(normalIndex[0]);
      tmp_normalIndices.push_back(normalIndex[1]);
      tmp_normalIndices.push_back(normalIndex[2]); 
    }
  }

  // organize temporary data into
  // proper storage and log progress
  printf("\nLoading: %s:\n\n",mesh->name.c_str());

  for (unsigned int i=0; i<tmp_vertexIndices.size(); i++) {
    // read vertex at each index
    // read in groups of 3, these are the coordinates of polygons
    // for example:
    //    first polygon is index 5 1 4
    //    can verify these are the first 3 coordinates displayed
    //    using the display function and obj file

    // log vertex progress print function:


    std::cout<<"v-"<<i+1<<": ";
    std::cout<<glm::to_string(mesh->vertices[tmp_vertexIndices[i]-1].position)<<std::endl;
    if ( (i+1) % 3 == 0) std::cout<<std::endl;
  }
  
  std::cout<<std::endl;
  
  for (unsigned int i=0; i<tmp_uvIndices.size(); i++) {
    // set texcoord for each vertex
    mesh->vertices[tmp_uvIndices[i]-1].texcoord = tmp_UVs[tmp_uvIndices[i]-1];

    // log uv progress print function:
    std::cout<<"uv-"<<i+1<<": ";
    std::cout<<glm::to_string(mesh->vertices[tmp_uvIndices[i]-1].texcoord)<<std::endl;
    if ( (i+1) % 3 == 0) std::cout<<std::endl;
  }

  std::cout<<std::endl;

  for (unsigned int i=0; i<tmp_normalIndices.size(); i++) {
    // set texcoord for each vertex
    mesh->vertices[tmp_normalIndices[i]-1].normal = tmp_normals[tmp_normalIndices[i]-1];

    // log normal progress print function:
    std::cout<<"n-"<<i+1<<": ";
    std::cout<<glm::to_string(mesh->vertices[tmp_normalIndices[i]-1].normal)<<std::endl;
    if ( (i+1) % 3 == 0) std::cout<<std::endl;
  }
  
  printf("Finished Loading: %s:\n",mesh->name.c_str());

  return;
}