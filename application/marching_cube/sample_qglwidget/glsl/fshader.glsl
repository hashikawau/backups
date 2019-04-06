
//uniform sampler2D texture;

//varying vec2 v_texcoord;
varying vec3 v_color;

void main(){
    // Set fragment color from texture
    //gl_FragColor = texture2D(texture, v_texcoord);
    gl_FragColor = vec4(v_color, 1.0);
}

