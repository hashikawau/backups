#version 400

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_color;

out vec3 v_color;

uniform mat4 u_mvpMatrix;

void main(){
    //gl_Position = ftransform();
    //v_color = gl_Color.xyz;
    gl_Position = u_mvpMatrix * vec4(a_vertex, 1.0);
    v_color = a_vertex;
}
