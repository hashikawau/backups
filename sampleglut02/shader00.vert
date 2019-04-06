

uniform mat4 u_mvMatrix;
uniform mat4 u_mvpMatrix;
uniform mat3 u_nMatrix;
uniform float u_timeRatio;

attribute vec4 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_texture;

varying vec3 position;
varying vec3 normal;

void main(){
    vec4 vertex = vec4(a_vertex);
    //vertex.x *= 5.0;
    //vertex.y *= 10.0;
    //vertex.z *= 10.0;
    //vertex.w /= 1.0;
    
    position = vec3(u_mvMatrix * vertex);
    normal = u_nMatrix * a_normal;
    //normal = normalize(u_nMatrix * a_normal);
    //normal = normalize(gl_NormalMatrix * a_normal);
    
    vec3 light = normalize(vec3(0.0, 10.0, 10.0) - position);
    //vec3 light = normalize(u_lightPosition - position);
    float diffuse = dot(light, normal);

    vec4 ambient = vec4(1.0) * 0.5 * (1.0 + sin(2 * 3.14 * u_timeRatio));
    if(diffuse < 0.0){
        diffuse = 0.0;
    }
	
    gl_FrontColor = vec4(0.3, 0.3, 1.0, 1.0) * diffuse + ambient;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_Position = u_mvpMatrix * vertex;
}


