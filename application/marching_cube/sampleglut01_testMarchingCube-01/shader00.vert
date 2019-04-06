

uniform mat4 u_mvMatrix;
uniform mat4 u_mvpMatrix;
uniform mat3 u_nMatrix;
uniform vec3 u_lightPosition;
uniform float u_timeRatio;

attribute vec4 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

varying vec3 v_vertexPos;
varying vec3 v_normalVec;
varying vec2 v_texCoord;

varying vec3 v_lightPos;
varying vec4 v_ambient;
varying float v_diffuse;
varying float v_specular;

void main(){
    float magX = 1.0;
    float magY = 1.0;
    float magZ = 1.0;
    float magW = 1.0;
    vec4 vertex = vec4(a_vertex);
    vec3 normal = vec3(a_normal);
    //vertex.z += -1.0;
/*    vertex.x *= magX;*/
/*    normal.x /= magX;*/
/*    vertex.y *= magY;*/
/*    normal.y /= magY;*/
/*    vertex.z *= magZ;*/
/*    normal.z /= magZ;*/
/*    vertex.w /= magW;*/

    mat4 tMatrix = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, -2.0, 1.0);
    mat4 mvMatrix = tMatrix * u_mvMatrix;
    mat4 mvpMatrix = gl_ProjectionMatrix * mvMatrix;
    
    vec3 lightPos = vec3(100.0, 100.0, 0.0);
    vec3 vertexPos = (mvMatrix * vertex).xyz;
    //vec3 vertexPos = (u_mvMatrix * vertex).xyz;
    vec3 normalVec = u_nMatrix * normal;
    
    vec4 ambient = vec4(1.0) * u_timeRatio;
    v_ambient = vec4(a_vertex.xyz + 0.5, 1.0);
    
    v_vertexPos = vertexPos;
    //v_vertexPos = a_vertex.xyz;
    v_normalVec = normalVec;
    v_texCoord = a_texCoord;
    v_lightPos = lightPos;
    //====================
    gl_Position = u_mvpMatrix * vertex;
    gl_Position = mvpMatrix * vertex;
}


