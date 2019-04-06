

uniform sampler2D u_texture0;
uniform int u_time;

/*varying vec3 v_eye;*/
/*varying vec3 v_normal;*/
varying vec2 v_texCoord;

varying vec4 v_ambient;
varying float v_diffuse;
varying float v_specular;

void main(){
    //gl_FragColor = gl_Color;
    //float ratio = u_time / u_time;
    //if(isinf(ratio)){
    //    gl_FragColor = gl_Color;
    //}else{
    //    gl_FragColor = gl_Color;
    //}
    
    vec4 color = vec4(
        texture2D(u_texture0, v_texCoord).r * 1.0,
        texture2D(u_texture0, v_texCoord).r * 1.0,
        texture2D(u_texture0, v_texCoord).r * 1.0,
        1.0);
    
    //gl_FragColor = gl_Color;
    //gl_FragColor *= (v_diffuse + v_specular);
    gl_FragColor = 
        //v_ambient
        color * v_diffuse * 0.3
        + color * v_specular * 0.1;
    
    //gl_FragColor += v_ambient;
}

