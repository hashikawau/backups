

uniform sampler2D u_texture0;
uniform int u_time;

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;

varying float diffuse;

void main(){
    //gl_FragColor = gl_Color;
    //float ratio = u_time / u_time;
    //if(isinf(ratio)){
    //    gl_FragColor = gl_Color;
    //}else{
    //    gl_FragColor = gl_Color;
    //}
        
    //gl_FragColor = texture2D(u_texture0, gl_TexCoord[0].st);
    //gl_FragColor = vec4(v_texCoord, 0.0, 1.0);
    //gl_FragColor = texture2D(u_texture0, vec2(1.0, 1.0));
    gl_FragColor = texture2D(u_texture0, v_texCoord);
    
    gl_FragColor = gl_Color;
    gl_FragColor *= gl_Color;
}

