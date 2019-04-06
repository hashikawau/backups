#version 400

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoord;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_texCoord;

uniform mat4 u_mvMatrix;
uniform mat3 u_normalMatrix;
uniform mat4 u_mvpMatrix;

void main(){
    v_normal = normalize(u_normalMatrix * a_normal);
    v_position = vec3(u_mvMatrix * vec4(a_vertex, 1.0));
    
    gl_Position = u_mvpMatrix * vec4(a_vertex, 1.0);
}
