

uniform sampler2D u_texture0;
uniform int u_time;

varying vec3 v_vertexPos;
varying vec3 v_normalVec;
varying vec2 v_texCoord;

varying vec3 v_lightPos;
varying vec4 v_ambient;
varying float v_diffuse;
varying float v_specular;

void main(){
    vec4 color = vec4(
        texture2D(u_texture0, v_texCoord).r * 0.5,
        texture2D(u_texture0, v_texCoord).r * 0.9,
        texture2D(u_texture0, v_texCoord).r * 0.5,
        1.0);
    
    vec3 vertexPos = v_vertexPos;
    vec3 normalVec = normalize(v_normalVec);
    vec3 lightVec = normalize(v_lightPos - vertexPos);
    
    float diffuse = dot(lightVec, normalVec);
    float specular = 0.0;
    if(diffuse > 0.0){
        float exp = 0.0;
        vec3 eyeVec = normalize(-vertexPos);
        
        //vec3 halfVec = normalize(lightVec + eyeVec);
        //exp = max(dot(halfVec, normalVec), 0.0);
        
        vec3 reflectionVec = normalize(reflect(-lightVec, normalVec));
        exp = max(dot(reflectionVec, eyeVec), 0.0);
        
        specular = pow(100.0, exp);
    }else{
        diffuse = 0.0;
    }
    
    //gl_FragColor = gl_Color;
    //gl_FragColor *= (v_diffuse + v_specular);
    gl_FragColor = vec4(v_vertexPos, 1.0);
        //color * 0.5
        //+ color * diffuse * 0.1
        //+ vec4(1.0) * specular * 0.1;
    //gl_FragColor += v_ambient;
}

