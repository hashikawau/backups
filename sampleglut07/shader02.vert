

uniform mat4 u_mvMatrix;
uniform mat4 u_mvpMatrix;
uniform mat3 u_nMatrix;
uniform vec3 u_lightPosition;
uniform float u_timeRatio;

attribute vec4 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;

varying float v_diffuse;

void main(){
    float magX = 1.0;
    float magY = 1.0;
    float magZ = 1.0;
    float magW = 1.0;
    vec4 vertex = vec4(a_vertex);
    vec3 normal = vec3(a_normal);
    vertex.x *= magX;
    normal.x /= magX;
    vertex.y *= magY;
    normal.y /= magY;
    vertex.z *= magZ;
    normal.z /= magZ;
    vertex.w /= magW;
    
    v_position = vec3(u_mvMatrix * vertex);
    v_normal = u_nMatrix * normal;
    //v_normal = normalize(u_nMatrix * normal);
    //v_normal = normalize(gl_NormalMatrix * a_normal);
    v_texCoord = a_texCoord;
    
    vec3 light = normalize(vec3(0.0, 10.0, 10.0) - v_position);
    //vec3 light = normalize(u_lightPosition - v_position);
    v_diffuse = dot(light, v_normal);

    vec4 ambient = vec4(1.0) * 0.5 * (1.0 + sin(2 * 3.14 * u_timeRatio));
    if(v_diffuse < 0.0){
        v_diffuse = 0.0;
    }
	
    gl_FrontColor = vec4(0.3, 0.3, 1.0, 1.0) * v_diffuse;// + ambient;
    //gl_TexCoord[0] = vec4(a_texCoord, 0.0, 1.0);
    gl_Position = u_mvpMatrix * vertex;
    //gl_Position = gl_ModelViewProjectionMatrix * a_vertex;
}


