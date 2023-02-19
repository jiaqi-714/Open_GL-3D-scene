#version 330 core

// Inputs
in vec3 v_pos;
in vec3 v_normal;
in vec2 v_texco;

// Maps
uniform sampler2D u_diff_map;
uniform sampler2D u_spec_map;

// Lighting parameters
uniform vec3 u_light_pos;
uniform vec3 u_light_color;
uniform mat4 v;

// Material parameters
uniform vec3 u_diffuse;
uniform vec3 u_emissive;
uniform float u_shininess = 20;

// second light parameters
uniform vec3 u_light2_pos;
uniform vec3 u_light2_color;

//direction light parameter
uniform vec3 sun_light_dir;
uniform vec3 sun_light_color;

// Outputs
out vec4 color;

vec3 srgb_to_linear(vec3 colour) {
    return pow(colour, vec3(2.2));
}

vec3 linear_to_srgb(vec3 colour) {
    return pow(colour, vec3(1 / 2.2));
}

vec3 direcLight(vec3 light_pos, vec3 light_color) {

    vec3 normal = normalize(v_normal);
    //diffuse light 
    vec3 light_vec = (v * vec4(light_pos, 1)).xyz - v_pos;     // from vertex to light vector
    vec3 light_dir = normalize(light_vec);              // from vertex to light direct
    vec3 view_dir = normalize(-v_pos);                  // from vertex to camera

    vec3 diff_col = srgb_to_linear(u_diffuse * texture(u_diff_map, v_texco).rgb);
    vec3 spec_col = srgb_to_linear(texture(u_spec_map, v_texco).rgb);
    vec3 light_col = srgb_to_linear(light_color);  // color of direcLight

    vec3 diffuse = diff_col * max(dot(normal, light_dir), 0) * light_col;
    vec3 specular;
    bool use_blinn = true;
    if (use_blinn) {
        vec3 halfway = normalize(light_dir + view_dir);
        specular = spec_col * pow(max(dot(halfway, normal), 0), u_shininess) * light_col;
    } else {
        vec3 reflection = reflect(-light_dir, normal);
        specular = spec_col * pow(max(dot(reflection, view_dir), 0), u_shininess) * light_col;
    }

    vec3 color_linear = vec3(0, 0, 0);
    color_linear += diffuse;
    color_linear += specular;
    

    return (linear_to_srgb((color_linear))) * 0.2;
}

vec3 pointLight(vec3 light_pos, vec3 light_color) {
    vec3 normal = normalize(v_normal);
    //diffuse light 
    vec3 light_vec = (v * vec4(light_pos, 1)).xyz - v_pos;       // from vertex to light vector
    vec3 light_dir = normalize(light_vec);              // from vertex to light direct
    vec3 view_dir = normalize(-v_pos);                  // from vertex to camera
    float light_dist = length(light_vec);               // light distance

    vec3 diff_col = srgb_to_linear(u_diffuse * texture(u_diff_map, v_texco).rgb);
    vec3 spec_col = srgb_to_linear(texture(u_spec_map, v_texco).rgb);
    vec3 light_col = srgb_to_linear(light_color);

    vec3 diffuse = diff_col * max(dot(normal, light_dir), 0) * light_col;
    vec3 specular;
    bool use_blinn = true;
    if (use_blinn) {
        vec3 halfway = normalize(light_dir + view_dir);
        specular = spec_col * pow(max(dot(halfway, normal), 0), u_shininess) * light_col;
    } else {
        vec3 reflection = reflect(-light_dir, normal);
        specular = spec_col * pow(max(dot(reflection, view_dir), 0), u_shininess) * light_col;
    }

    vec3 color_linear = vec3(0, 0, 0);

    color_linear += diffuse;
    color_linear += specular;

    // calculate point light contribution
    float attenuation = 1 / (1 + light_dist * 0.5);

    return (linear_to_srgb((color_linear) * attenuation)) * 0.8;
}

void main() {

    vec3 emit_col = srgb_to_linear(u_emissive);
    vec4 surface_colour = texture(u_diff_map, v_texco);
    vec3 ambient = vec3(0.1) * surface_colour.rgb;
    color = vec4(pointLight(u_light2_pos, u_light2_color), 1) + 
            vec4(direcLight(sun_light_dir, sun_light_color), 1) +
            vec4(pointLight(u_light_pos, u_light_color), 1) +
            vec4(linear_to_srgb((emit_col)), 1) +
            vec4(ambient, 1);
}

    // vec3 normal = normalize(v_normal);
    // //diffuse light 
    // vec3 light_vec = mat3(v) * u_light_pos - v_pos; // from vertex to light vector
    // vec3 light_dir = normalize(light_vec);          // from vertex to light direct
    // vec3 view_dir = normalize(-v_pos);              // from vertex to camera
    // float light_dist = length(light_vec);           // light distance

    // vec3 diff_col = srgb_to_linear(u_diffuse * texture(u_diff_map, v_texco).rgb);
    // vec3 spec_col = srgb_to_linear(texture(u_spec_map, v_texco).rgb);
    
    // vec3 light_col = srgb_to_linear(u_light_color);

    // vec3 diffuse = diff_col * max(dot(normal, light_dir), 0) * light_col;
    // vec3 specular;
    // bool use_blinn = true;
    // if (use_blinn) {
    //     vec3 halfway = normalize(light_dir + view_dir);
    //     specular = spec_col * pow(max(dot(halfway, normal), 0), u_shininess) * light_col;
    // } else {
    //     vec3 reflection = reflect(-light_dir, normal);
    //     specular = spec_col * pow(max(dot(reflection, view_dir), 0), u_shininess) * light_col;
    // }

    // vec3 color_linear = vec3(0.05) * diff_col;

    // color_linear += diffuse;
    // color_linear += specular;

    // // calculate emissive contribution
    // color_linear += emit_col;

    // // calculate point light contribution
    // float attenuation = 1 / (1 + light_dist * 0.3);