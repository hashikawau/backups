

uniform mat4 u_mvpMatrix;

void main(){
    
    gl_FrontColor = gl_Color;
    gl_Position = u_mvpMatrix * gl_Vertex;
    
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    return;
}
