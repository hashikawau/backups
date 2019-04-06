

varying vec3 position;
varying vec3 normal;


void main(){
    position = vec3(gl_ModelViewMatrix * gl_Vertex);
    normal = normalize(gl_NormalMatrix * gl_Normal);
    //vec3 light = normalize(gl_LightSource[0].position.xyz - position);
    //float diffuse = dot(light, normal);
    
    //gl_FrontColor = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * diffuse;
    
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

