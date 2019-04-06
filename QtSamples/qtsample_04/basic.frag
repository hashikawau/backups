#version 400

in vec3 v_frontColor;
in vec3 v_backColor;
in vec2 v_texCoord;

void main(){
    //gl_FragColor = vec4(1.0);
    
    const float scale = 1.0;
    bvec2 toDiscard = greaterThan(fract(v_texCoord * scale), vec2(0.05, 0.05));
    
    if(all(toDiscard)){
         discard;
         if(gl_FrontFacing){
            gl_FragColor = vec4(v_frontColor, 1.0);
        }else{
            gl_FragColor = mix(vec4(v_backColor, 1.0),
                vec4(vec3(0.5), 1.0),
                0.5);
        }
    }else{
         if(gl_FrontFacing){
            gl_FragColor = vec4(v_frontColor, 1.0);
        }else{
            gl_FragColor = mix(vec4(v_backColor, 1.0),
                vec4(vec3(0.5), 1.0),
                0.5);
            //discard;
        }
    }
}
