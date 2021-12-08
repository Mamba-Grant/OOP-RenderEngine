#pragma once

// class which contains all light objects

class point_light {
  public:
  glm::vec3 position;
  glm::vec3 radius;
};

class directional_light {
  public:
  glm::vec3 position;
  glm::vec3 angle;
};

class spot_light {
  public:
  glm::vec3 position;
  glm::vec3 angle;
  glm::vec3 falloff;
};

class generic_light {
  public:
  point_light* point_light_ptr = NULL;
  directional_light* directional_light_ptr = NULL;
  spot_light* spot_light_ptr = NULL;
};