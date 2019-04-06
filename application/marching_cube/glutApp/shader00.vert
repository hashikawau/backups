

uniform mat4 u_mvpMatrix;

attribute vec4 a_vertex;

varying vec4 v_vertex;

void main(){
    
    gl_FrontColor = gl_Color;
    //gl_Position = vec4(0);
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_Position = u_mvpMatrix * gl_Vertex;
    gl_Position = u_mvpMatrix * a_vertex;
    
    v_vertex = a_vertex;
    //return;
}
