#ifndef COMP3421_TUTORIAL_08_LIGHT_HPP
#define COMP3421_TUTORIAL_08_LIGHT_HPP

#include <glm/glm.hpp>

struct directional_light_t {
    glm::vec3 direction;
    glm::vec3 color;
};

struct point_light_t {
    // TODO: change fields
    glm::vec3 pos;
    glm::vec3 color;
};

#endif //COMP3421_TUTORIAL_08_LIGHT_HPP
