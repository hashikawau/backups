
uniform mat4 mvp_matrix;

attribute vec3 a_position;
attribute vec3 a_color;

varying vec3 v_color;

void main(){
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * vec4(a_position, 1.0);

    
    v_color = a_color;
}
