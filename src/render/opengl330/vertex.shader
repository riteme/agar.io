#version 130

in vec3 position_data;
in vec4 color_data;
in vec2 texcoord_data;
in vec3 normal_data;

out vec4 position;
out vec4 color;
out vec2 texcoord;
out vec3 normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
    position = projection * view * model * vec4(position_data, 1.0);
    color = color_data;
    texcoord = texcoord_data;
    normal = normal_data;
}