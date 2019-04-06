#version 400

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoord;

out vec3 v_frontColor;
out vec3 v_backColor;
out vec2 v_texCoord;

uniform mat4 u_mvMatrix;
uniform mat3 u_normalMatrix;
uniform mat4 u_mvpMatrix;

struct LightInfo{
    vec3 Position;
    vec3 La;
    vec3 Ld;
    vec3 Ls;
};
struct MaterialInfo{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;
};

LightInfo u_light = {
     vec3(0.0, 0.0, 20.0),
     vec3(1.0),
     vec3(1.0),
     vec3(1.0)
};
MaterialInfo u_material = {
    vec3(0.0, 0.0, 0.2),
    vec3(0.0, 0.0, 0.2),
    vec3(1.0, 1.0, 1.0),
    10.0
};

vec3 getDiffuseAndSpecular(vec3 eyePosition, vec3 normal);

void main(){

    vec3 Iambient = u_light.La * u_material.Ka;

    vec3 normal = normalize(u_normalMatrix * a_normal);
    vec3 eyePosition = vec3(u_mvMatrix * vec4(a_vertex, 1.0));
    
    v_frontColor = Iambient + getDiffuseAndSpecular(eyePosition, normal);
    v_backColor = Iambient + getDiffuseAndSpecular(eyePosition, -normal);
    v_texCoord = a_texCoord;

    gl_Position = u_mvpMatrix * vec4(a_vertex, 1.0);
}

vec3 getDiffuseAndSpecular(vec3 eyePosition, vec3 normal){
    vec3 s = normalize(u_light.Position - eyePosition);
    float sDotN = dot(s, normal);
    
    vec3 Idiffuse = vec3(0.0);
    vec3 Ispecular = vec3(0.0);
    if(sDotN > 0.0){
        Idiffuse = u_light.Ld * u_material.Kd * sDotN;
        
        //vec3 r = normalize(-s + 2 * dot(s, normal) * normal);
        vec3 r = reflect(-s, normal);
        vec3 v = normalize(-eyePosition.xyz);
        Ispecular = u_light.Ls * u_material.Ks
            * pow(max(dot(r, v), 0.0), u_material.Shininess);
            
        //if(dot(r, v) <= 0.0) Ispecular = vec3(1.0);
    }
    return Idiffuse + Ispecular;
    //return vec3(0.0);
}
