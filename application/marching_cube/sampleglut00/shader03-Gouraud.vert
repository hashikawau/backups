

uniform mat4 u_mvMatrix;
uniform mat4 u_mvpMatrix;
uniform mat3 u_nMatrix;
uniform vec3 u_lightPosition;
uniform float u_timeRatio;

attribute vec4 a_vertex;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

/*varying vec3 v_eye;*/
/*varying vec3 v_normal;*/
varying vec2 v_texCoord;

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
        0.0, 0.0, -1.0, 1.0);
    mat4 mvMatrix = tMatrix * u_mvMatrix;
    mat4 mvpMatrix = gl_ProjectionMatrix * mvMatrix;
    
    vec3 lightPos = vec3(0.0, 100.0, 100.0);
    vec3 vertexPos = (mvMatrix * vertex).xyz;
    //vec3 vertexPos = (u_mvMatrix * vertex).xyz;
    vec3 normalVec = u_nMatrix * normal;
    vec3 eyeVec = normalize(-vertexPos);
    vec3 lightVec = lightPos - vertexPos;
    float lightDist = length(lightVec);
    lightVec = normalize(lightVec);
    
    float dotLightNormal = dot(lightVec, normalVec);
    if(dotLightNormal < 0.0){
        dotLightNormal = 0.0;
    }
    float dotEyeNormal = dot(eyeVec, normalVec);
    if(dotEyeNormal < 0.0){
        dotEyeNormal = 0.0;
    }
    
    v_texCoord = a_texCoord;
    //v_texCoord = vec2(dotLightNormal, dotEyeNormal);
    //v_texCoord = vec2(dotEyeNormal, dotLightNormal);
    v_diffuse = dot(lightVec, normalVec);
    v_specular = 0.0;
    if(v_diffuse > 0.0){
        float exp = 0.0;
        
        //vec3 halfVec = normalize(lightVec + eyeVec);
        //exp = max(dot(halfVec, normalVec), 0.0);
        
        vec3 reflectionVec = normalize(reflect(-lightVec, normalVec));
        exp = max(dot(reflectionVec, eyeVec), 0.0);
        
        v_specular = pow(100.0, exp);
    }else{
        v_diffuse = 0.0;
    }
    v_ambient = vec4(0.0f, 1.0f, 0.0f, 1.0f) * 0.5f * (1.0 + sin(2 * 3.14 * u_timeRatio));
	
    //====================
    gl_Position = u_mvpMatrix * vertex;
    gl_Position = mvpMatrix * vertex;
}


