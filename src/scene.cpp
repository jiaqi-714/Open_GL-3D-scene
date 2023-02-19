#include <tute08/scene.hpp>

scene_t make_scene() {
    camera_t cam1 = make_camera({ 0, 1.1f, -8 }, { 0, 0, 0 }, false,1);
	camera_t cam2 = make_camera({ 0, 1.0f, -5 }, { 0, 0, 0 }, true,2);
	camera_t cam3 = make_camera({ 0, 0.9f, -5 }, { 0, 0, 0 }, false,3);

	directional_light_t sun_light = {
	    glm::vec3{ 100, 100, 0.0 }, //direction of sun
	    glm::vec3{ 1, 1, 1 } 		//color of sun
    };

	point_light_t light = {
	    glm::vec3{ 0, 5, 0 },
	    glm::vec3{ 1, 1, 1 }		//color of light 1
    };

	point_light_t light2 = {
	    glm::vec3{ 0, 3, 0 },
	    glm::vec3{ 1, 1, 1 }		//color of light 2
    };
	
    node_t torus5 = {
	    node_t::TORUS,
	    make_torus(
		    { 0.5f, 1.f, 32 },
		    { "res/textures/torus/marble_diff.jpg", "res/textures/torus/marble_diff.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { 0, 1, 0 }),
		glm::vec3 (0, 0, 0),
	    {  }
    };

    node_t sphere3 = {
	    node_t::SPHERE,
	    make_sphere(
		    { 16, 16 },
		    { "res/textures/sphere/gold_diff.jpg", "res/textures/sphere/gold_spec.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { 0, 1, 0 }) *
		glm::scale(glm::mat4(1), { 1, 1, 1 })
		,
		glm::vec3 (0, 0, 0),
	    { torus5 }
    };

    node_t torus4 = {
	    node_t::TORUS,
	    make_torus(
		    { 0.5f, 1.f, 32 },
		    { "res/textures/torus/marble_diff.jpg", "res/textures/torus/marble_diff.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { -1, 0.2, 2 }),
		glm::vec3 (0, 0, 0),
	    { sphere3 }
    };

    node_t pyramid = {
	    node_t::PYRAMID,
	    make_pyramid(
		    { 1, 1, 1 },
		    { "res/textures/brick/brick.png", "res/textures/brick/brick.png" }
	    ),
	    glm::translate(glm::mat4(1), { 0, -3, 0 }) *
		glm::scale(glm::mat4(1), { 2, 2, 2 }),
		glm::vec3 (0, 0, 0),
	    {  }
    };

    node_t torus3 = {
	    node_t::TORUS,
	    make_torus(
		    { 0.5f, 1.f, 32 },
		    { "res/textures/torus/marble_diff.jpg", "res/textures/torus/marble_diff.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { -3, 3, 0 }),
		glm::vec3 (0, 0, 0),
	    { pyramid }
    };

    node_t torus2 = {
	    node_t::TORUS,
	    make_torus(
		    { 0.5f, 1.f, 32 },
		    { "res/textures/torus/marble_diff.jpg", "res/textures/torus/marble_diff.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { 0, 1, 0 }),
	    // * glm::rotate(glm::mat4(1), glm::pi<float>() / 2, { 0, 1, 0 })
	    // * glm::rotate(glm::mat4(1), glm::pi<float>() / 2, { 0, 0, 1 }),
		glm::vec3 (0, 0, 0),
	    { }
    };

    node_t sphere2 = {
	    node_t::SPHERE,
	    make_sphere(
		    { 16, 16 },
		    { "res/textures/sphere/gold_diff.jpg", "res/textures/sphere/gold_spec.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { 0, 2, 0 }) *
		glm::scale(glm::mat4(1), { 1, 1, 1 })
		,
		glm::vec3 (0, 0, 0),
	    { torus2 }
    };

    node_t cube = {
	    node_t::CUBE,
	    make_volume(
		    { 1, 1, 1 },
		    { "res/textures/volume/bricks_diff.jpg", "res/textures/volume/bricks_spec.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { 3, 1, 3 }),
		glm::vec3 (0, 0, 0),
	    { sphere2 }
    };

    node_t sphere = {
	    node_t::SPHERE,
	    make_sphere(
		    { 16, 16 },
		    { "res/textures/sphere/gold_diff.jpg", "res/textures/sphere/gold_spec.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { 0, 0, 0 }) *
		glm::scale(glm::mat4(1), { 0.3, 0.3, 0.3 }),
		glm::vec3 (0, 0, 0),
	    { }
    };

    node_t torus = {
	    node_t::TORUS,
	    make_torus(
		    { 0.5f, 1.f, 32 },
		    { "res/textures/torus/marble_diff.jpg", "res/textures/torus/marble_diff.jpg" }
	    ),
	    glm::translate(glm::mat4(1), { 2.5f, 1.1f, 0 })
	    * glm::rotate(glm::mat4(1), glm::pi<float>() / 2, { 0, 1, 0 })
	    * glm::rotate(glm::mat4(1), glm::pi<float>() / 2, { 0, 0, 1 }),
		glm::vec3 (0, 0, 0),
	    { sphere }
    };

    material_param_t mtl_light_mesh;
    mtl_light_mesh.emissive = glm::vec3(1, 1, 1);
    node_t light_mesh = {
	    node_t::LIGHT_MESH,
	    make_sphere(
		    { 4, 4 },
		    mtl_light_mesh
	    ),
	    glm::translate(glm::mat4(1), { 0, 5, 0 })
	    * glm::scale(glm::mat4(1), { 0.1, 0.1, 0.1 }),
		glm::vec3 (0, 0, 0),
	    { }
    };

    node_t moving_light = {
	    node_t::MOVINGLIGHT,
	    make_sphere(
		    { 4, 4 },
		    mtl_light_mesh
	    ),
	    glm::translate(glm::mat4(1), { 0, 5, 0 })
		* glm::scale(glm::mat4(1), { 0.1, 0.1, 0.1 }),
		glm::vec3 (0, 0, 0),
	    { }
    };

    node_t ground = {
	    node_t::GROUND,
	    make_volume(
		    { 100, 0, 100 },
		    { "res/textures/plank/planks.png", "res/textures/plank/planksSpec.png" }
	    ),
	    glm::mat4(1),
		glm::vec3 (0, 0, 0),
	    { cube, torus, light_mesh, moving_light, torus3, torus4}
    };

    return scene_t{ cam1, cam2, cam3, light, light2, sun_light, moving_light, ground };
}

camera_t switch_camera(GLFWwindow *win, scene_t s, camera_t current_camera) {
	camera_t cam1 = s.cam1;
	camera_t cam2 = s.cam2;
	camera_t cam3 = s.cam3;
	if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		if (current_camera.id == 1) {
			return cam2;
		}
		else if (current_camera.id  == 2) {
			return cam3;
		}
		else if (current_camera.id  == 3) {
			return cam1;
		}
	}
	return current_camera;
};