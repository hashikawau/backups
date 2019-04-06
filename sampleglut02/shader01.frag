

uniform sampler2D u_texture;
uniform int u_time;

varying vec3 position;
varying vec3 normal;

void main(){
    //gl_FragColor = gl_Color;
    float ratio = u_time / u_time;
    if(isinf(ratio)){
        gl_FragColor = gl_Color;
    }else{
        gl_FragColor = gl_Color;
    }
        
    //gl_FragColor = Texture2D(u_texture);
    //gl_FragColor = gl_TexCoord[0];
}

