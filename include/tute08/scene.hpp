#ifndef COMP3421_TUTORIAL_08_SCENE_HPP
#define COMP3421_TUTORIAL_08_SCENE_HPP

#include <glad/glad.h>

#include <glm/ext.hpp>

#include <tute08/camera.hpp>
#include <tute08/light.hpp>
#include <tute08/primitives.hpp>


struct node_t {
    /**
     * The different types of models in our scene.
     */
    enum {
        MOVINGLIGHT,
        PYRAMID,
        CUBE,
        SPHERE,
        TORUS,
        GROUND,
        LIGHT_MESH
    } kind;
    model_t obj;
    glm::mat4 transform;
    glm::vec3 pos;
    std::vector<node_t> children;
};

/**
 * Our scene consists of a simple camera and the graph of all objects.
 *
 * Note that every node is the same size because all the models are the same size.
 * This isn't necessarily true in the real world.
 * How might one deal with different node sizes?
 */
struct scene_t {
    camera_t cam1;
    camera_t cam2;
    camera_t cam3;

    point_light_t point_light;
    point_light_t point_light2;
    directional_light_t sun_light;
    node_t moving_light;

    node_t root;
};

/**
 * Create our scene in whatever fashion we desire.
 *
 * It is important to note that this function takes the role of a level loader.
 * Thus, we'll almost always be changing this when we want different things in-scene.
 *
 * @return Our scene
 */
scene_t make_scene();

camera_t switch_camera(GLFWwindow *win, scene_t s, camera_t current_camera);



#endif //COMP3421_TUTORIAL_08_SCENE_HPP
