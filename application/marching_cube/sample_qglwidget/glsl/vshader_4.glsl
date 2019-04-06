
uniform mat4 mvp_matrix;

attribute vec3 a_position;
//attribute vec3 a_color;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;
//varying vec3 v_color;

void main(){
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * vec4(a_position, 1.0);
//    gl_Position = a_position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
    
//    v_color = a_color;
}
