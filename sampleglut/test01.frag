

//uniform sampler2D texture;

varying vec3 position;
varying vec3 normal;

void main(){
    //gl_FragColor = gl_Color;
    gl_FragColor = gl_TexCoord[0];
}

