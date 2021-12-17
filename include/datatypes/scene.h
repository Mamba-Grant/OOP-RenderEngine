#pragma once
#include "generic_class.h"
#include "../tutorial/Camera.h"
#include <vector>

class scene {
public:
  Camera* MAIN_SCENE_CAMERA;
  directional_light* SCENE_MAIN_LIGHT;
  std::vector<generic_container*> SCENE_CHILDREN;

};