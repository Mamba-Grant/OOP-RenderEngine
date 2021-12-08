#pragma once

// objects to contain empties
//
// these are (usually) not rendered 
// but are extremely useful for a variety of things
//
// this specific implementation is intended to
// be similar to blender's implementation

class axes_empty {
  public:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};

class sphere_empty {
  public:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  glm::vec3 radius;
};

class circle_empty {
  public:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  glm::vec3 radius;
};

class image_empty {
  public:
  std::string imagedir;
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};

class generic_empty {
  public:
  axes_empty* axes_empty_ptr;
  sphere_empty* sphere_empty_ptr;
  circle_empty* circle_empty_ptr;
  image_empty* image_empty_ptr;
};