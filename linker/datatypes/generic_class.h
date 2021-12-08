#pragma once

#include "bezier_curve.h"
#include "generic_empty.h"
#include "generic_light.h"
#include "geometry.h"
#include "shader.h"

class generic_container {
public:
  mesh* skinned_mesh_ptr = NULL;
  shader* shader_ptr = NULL;
  bezier_curve* bezier_curve_ptr = NULL;
  generic_light* generic_light_ptr = NULL;
  generic_empty* generic_empty_ptr = NULL;

  std::string name;
  generic_container* parent_ptr;

  // directory of JSON file for custom parameters
  // unnecessary but cool... I guess
  std::string custom_params; 


  // generic constructor (name & parent necessary)
  generic_container(std::string name, generic_container* parent_ptr)
    : name(name), parent_ptr(parent_ptr) {}

  // mesh only constructor
  generic_container(std::string name, mesh* skinned_mesh_ptr, generic_container* parent_ptr) 
    : skinned_mesh_ptr(skinned_mesh_ptr), name(name), parent_ptr(parent_ptr) {}

  // mesh/shader constructor
  generic_container(std::string name, mesh* skinned_mesh_ptr, shader* shader_ptr, generic_container* parent_ptr) 
    : skinned_mesh_ptr(skinned_mesh_ptr), shader_ptr(shader_ptr), name(name), parent_ptr(parent_ptr) {}

  // light only constructor
  generic_container(std::string name, generic_light* generic_light_ptr, generic_container* parent_ptr)
    : generic_light_ptr(generic_light_ptr), name(name), parent_ptr(parent_ptr) {}
};