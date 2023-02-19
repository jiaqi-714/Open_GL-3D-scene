# Assignment 2 Justification

If you think any of the questions within the sections are not applicable, please write "N/A".
This assignment is base on tut8 and tut5.

## Section 1: Creation and Use of 3D Objects

### 1a: Show that you have created or imported at least one 3D object that is visible in your application. Include references to where this is implemented in your code.

I have create a 3d pyramid for this, and use some 3d things from tut8. These 3d things are all in primitives.cpp, functions are 
mesh_t make_pyramid_mesh(), 
mesh_t make_torus_mesh(const torus_param_t &params), 
mesh_t make_sphere_mesh(const sphere_param_t &params),
mesh_t make_volume_mesh(const volume_param_t &params),
then make VAO of these things by mesh_t upload_mesh(const std::vector<vertex_t> &vertices, const std::vector<index_t> &indices)
make texture by GLuint upload_texture(const std::string &path)
texture and VAO is bind to each model for draw use.
above function are all in primitives.cpp.


### 1b: Describe your scene graph and the hierarchy within the scene. Include references to where this is implemented in your code.

some of the Hierarchy of 3d project is like this 
ground -> torus -> sphere
ground -> torus -> pyramid

### 1c: Describe how your objects are moving or animating in realtime. Include code references (line numbers and function names) to use of delta time and also how this affects the scene graph.

There is a light moving between two spline. 

animate comes from:
in animator.cpp, line 110, function animate
        // first calculate x, z position of bspline movement
        n->transform = animate(animator.spline_animation, now);        
        // then, increase this movement's y value by 3 unit3 to let this movement fly in the space
        n->transform = glm::translate(n->transform, {0, 3.0f, 0});         // important! use these code to control the fly path
        // then, scale this object to its 1/10
        n->transform = glm::scale(n->transform, {0.1f, 0.1f, 0.1f});

delta time is calculate by function float time_delta(), float time_now() in main.cpp, line 112, 
this is used in splines function in animator.cpp, line 21 to used in determine the period of the spline movement


### 1d: Describe how you have used parametric splines in your application. Include code references to the implementation of control point based curves in your project.

spline is calculate in glm::vec3 cubic(const std::vector<glm::vec3> &p, float t) in in animator.cpp, line 21.
this return a position of vec3 to be used in transform matrix.

glm::mat4 animate(const bspline_t &bspline, float now) in animator.cpp, line 34
this return a mat4 for transform use calculate by position return by spline function.

## Section 2: Camera

IMPORTANT: PRESS SPACE TO CHANGE THE CAMERA BETWEEN EACH OTHER

### 2a: Describe what controls the player should use to move the camera in your scene. Include code references to the implementation of delta time control of speed and use of user input in your project.

IMPORTANT: PRESS SPACE TO CHANGE THE CAMERA BETWEEN EACH OTHER
Camera angle is control by void update_cam_angles(camera_t &cam, GLFWwindow *win, float dt) in camera.cpp line 37. 
this get the delta movement of cursor by use (current cursor position - previous cursor position), this cursor delta movement
is used in calculate the angle of camera move.

Camera position is control by void update_cam_pos(camera_t &cam, GLFWwindow *win, float dt, glm::vec3 moving_light_pos) in camera.cpp, line 51
this get delta time of each frame to calculate how long should camera position go.

### 2b: Describe how your camera interacts with the scene. Is it able to "walk" on the Z-X plane or follow terrain? Include code references.

IMPORTANT: PRESS SPACE TO CHANGE THE CAMERA BETWEEN EACH OTHER
Achieve this by void update_cam_pos(camera_t &cam, GLFWwindow *win, float dt, glm::vec3 moving_light_pos) camera.cpp line 37, 
the important code is         
        if (cam.FPSMode) {
            cam.pos.y = 0.2f;
        }
this will fix the movement of camera on the ground, which is y = 0.2. FPSMode means this is a "walk" camera on the Z-X plane.


### 2c: Describe how the view of your scene can change from player controlled to application controlled (specify user input that makes this change happen). Include code references to use of parametric curves and delta time in the application controlled camera.

IMPORTANT: PRESS SPACE TO CHANGE THE CAMERA BETWEEN EACH OTHER
Achieve this by update the pos of moving object to a camera. I simplely attach the position of object which is animate by spline
to the camera. 
The function achieve is void update_cam_pos(camera_t &cam, GLFWwindow *win, float dt, glm::vec3 moving_light_pos) camera.cpp line 37,
important code of this is          
        if (cam.id == 3) {
            cam.pos = moving_light_pos;
        }
if this is a Cutscene Camera, then attach this position of camera to the object which is animated.

## Section 3: Lighting

### 3a: Describe where Diffuse Lighting is clear to see in your application. Include code references to your implemented lighting (including where this is implemented in your shaders).

Diffuse Lighting is clear in almost every object, but sphere and TORUS are the most clear, this is calculate in default.frag
function direcLight(vec3 light_pos, vec3 light_color) and pointLight(vec3 light_pos, vec3 light_color)

line 51 in direcLight(vec3 light_pos, vec3 light_color):
        vec3 diff_col = srgb_to_linear(u_diffuse * texture(u_diff_map, v_texco).rgb);
        vec3 light_col = srgb_to_linear(light_color);  // color of direcLight
        vec3 diffuse = diff_col * max(dot(normal, light_dir), 0) * light_col;

line 80 in pointLight(vec3 light_pos, vec3 light_color):
        vec3 diff_col = srgb_to_linear(u_diffuse * texture(u_diff_map, v_texco).rgb);
        vec3 light_col = srgb_to_linear(light_color);
        vec3 diffuse = diff_col * max(dot(normal, light_dir), 0) * light_col;

use the light_dir and vertex_normal to get the the intensity of light, and mutiply the color of the light and texture.

### 3b: Describe where Specular Lighting is clear to see in your application, including how the camera position affects the lighting. Include code references to your implemented lighting (including where this is implemented in your shaders).

Specular Lighting is clear in sphere, calculate in default.frag function 
direcLight(vec3 light_pos, vec3 light_color) and pointLight(vec3 light_pos, vec3 light_color) 

line 50 in direcLight(vec3 light_pos, vec3 light_color) and line 81 in pointLight(vec3 light_pos, vec3 light_color):
        vec3 spec_col = srgb_to_linear(texture(u_spec_map, v_texco).rgb);
        vec3 light_col = srgb_to_linear(light_color);
        vec3 specular;
        bool use_blinn = true;
        if (use_blinn) {
            vec3 halfway = normalize(light_dir + view_dir);
            specular = spec_col * pow(max(dot(halfway, normal), 0), u_shininess) * light_col;
in this assignment, blinn phong is used to calculate specular light, since it avoid the problem with Phong is that the angle between the view direction and the reflection direction has to be less than 90 degrees in order for the specular term to be non-zero.
the more less the angle between light_direction and view_direction, more intense will be in specular light.
    

### 3c: Describe which of your light(s) in your scene are point light(s) and how you have placed objects in the scene to clearly show the point lights functioning. Include code references to point light implementation.

just place the object near these two light.

Two point light is used in assignment, one is control by "q" "e" to moving its position, other one is fly and moving around the object
These two light is created in scene.cpp line 13, 18, 145 and 157

control the position of first light in main.cpp update_light(scene_t &scene, GLFWwindow *win, float dt) in line 37
update the position and color of first light to vertex shader and fragment shader in renderer.cpp, line 104

animate the second light is in animator.cpp animate(const animator_t &animator, scene_t &scene, float now), in line 117
update the position and color of second light to vertex shader and fragment shader in renderer.cpp, line 107.

One directional light is used in assignment, this create in scene.cpp line 8, 
update the position and color of directional light to vertex shader and fragment shader in renderer.cpp, line 112.

### 3d: Describe all the lights in your scene and what type they are. Include code references to implementation of the capability to work with an arbitrary number of lights.

Two point light is used in assignment, one is control by "q" "e" to moving its position, other one is fly and moving around the object
These two light is created in scene.cpp line 13, 18, 145 and 157

One directional light is used in assignment, this create in scene.cpp line 8, 
update the position and color of directional light to vertex shader and fragment shader in renderer.cpp, line 112.

The final light calculatation is created to two function, direcLight(vec3 light_pos, vec3 light_color) and pointLight(vec3 light_pos, vec3 light_color) in default.frag
when I want to create a new light, I can just pass the light position and light color to these function to calculate the light, then
add all of the light in the scene to get the final light in fragment shader. 


### 3e: Explain what maps you have used and which objects they are on. Your application should clearly show the effect these maps are having on lighting. Include code references to maps on objects and vertices as well as lighting code that uses the maps.

One object will be associated by two texture, First texture is normal texture map and second texture is specular map. 
object struct is like this 
struct model_t {
    mesh_t mesh;
    material_t material;
};
and material_t contain two map {
    GLuint diff_map;
    GLuint spec_map;
}
mesh_t contain the vertexs, vertex normal and vertexs texture coordinate of these texture, So we can use these information and 
light direction and light color to get our final color. 
The code is in fragment shader, function pointLight(vec3 light_pos, vec3 light_color) and direcLight(vec3 light_pos, vec3 light_color):
        vec3 diff_col = srgb_to_linear(u_diffuse * texture(u_diff_map, v_texco).rgb);
        vec3 spec_col = srgb_to_linear(texture(u_spec_map, v_texco).rgb);
        vec3 light_col = srgb_to_linear(light_color);
diff_col is the color from normal texture, spec_col is color from specular map, light_col is just light color.
then we use these color mutiple the intensity of diffuse light and specular light to get effect of these map.

## Section 4: Subjective Mark

### How have you fulfilled this requirement?

make a moving light...

### What is your vision for the scene you are showing?

Random places of object

### Are you referencing anything in this scene? Is this a quote or homage to any other art? Please describe it.

no

### Please give instructions for how a viewer/player should interact with this scene to see all the content you have created.

no

## Section 5 (optional): Code Style Feedback

### There are no marks assigned to code style in this assignment. However, if you would like to receive some feedback on your coding style, please point out a section of your code (up to 100 lines) and your tutor will give you some written feedback on the structure and readability of that code.



## Section 6 (optional): Use of External Libraries

### What does the library do?

no

### Why did you decide to use it?

no

### How does this integrate with the assignment project build system? Please include any instructions and requirements if a marker needs to integrate an external library.

no
