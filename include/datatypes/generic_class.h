#pragma once
#include "../tutorial/shaderClass.h"
#include "bezier_curve.h"
#include "generic_empty.h"
#include "generic_light.h"
#include "mesh.h"

class generic_container {
public:
  mesh* skinned_mesh_ptr = NULL;
  Shader* shader_ptr = NULL;
  bezier_curve* bezier_curve_ptr = NULL;
  generic_light* generic_light_ptr = NULL;
  generic_empty* generic_empty_ptr = NULL;

  std::string name;
  generic_container* parent_ptr;

  // directory of JSON file for custom parameters
  // unnecessary but cool... I guess
  std::vector<std::string> custom_params; 

  // generic_container();
  // // mesh only constructor
  // generic_container(mesh* skinned_mesh_ptr, std::string name, generic_container* parent_ptr) 
  //   : skinned_mesh_ptr(skinned_mesh_ptr), name(name), parent_ptr(parent_ptr) {}

};