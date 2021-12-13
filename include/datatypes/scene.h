#pragma once
#include "generic_class.h"
#include <vector>

class camera {
public:
  glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);  
  glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); 

  unsigned int height, width;

  camera(unsigned int width, unsigned int height, glm::vec3 Position)
  : width(width), height(height), Position(Position) {}

  void Matrix(float FOVdeg, float nearPlane, float farPlane, unsigned int& shader, const char* uniform) {
  // Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
  }
};

class scene {
public:
  camera* MAIN_SCENE_CAMERA;

  directional_light* SCENE_MAIN_LIGHT;
  shader* SCENE_CUBEMAP;

  std::vector<generic_container> SCENE_CHILDREN;
};