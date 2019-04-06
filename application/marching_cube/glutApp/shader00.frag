

//uniform mat4 u_mvpMatrix;
varying vec4 v_vertex;

void main(){
    
    gl_FragColor = gl_Color;
    //gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    gl_FragColor = v_vertex;
    
    //return;
}
