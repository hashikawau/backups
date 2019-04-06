#version 400

in vec3 v_position;
in vec3 v_normal;
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
    vec3(0.5, 0.5, 1.0),
    50.0
};

vec3 ads(){
    vec3 s = normalize(u_light.Position - v_position);
    vec3 v = normalize(-v_position);
    

    if(gl_FrontFacing){
        vec3 n = normalize(v_normal);
        //--->
        vec3 h = normalize(v + s);
        vec3 Iambient = u_light.La * u_material.Ka;
        vec3 Idiffuse = u_light.Ld * u_material.Kd * max(dot(s, n), 0.0);
        vec3 Ispecular = u_light.Ls * u_material.Ks * pow(max(dot(h, n), 0.0), u_material.Shininess);
        //<---
        return Iambient + Idiffuse + Ispecular;
    }else{
        vec3 n = normalize(-v_normal);
        //--->
        vec3 h = normalize(v + s);
        vec3 Iambient = u_light.La * u_material.Ka;
        vec3 Idiffuse = u_light.Ld * u_material.Kd * max(dot(s, n), 0.0);
        vec3 Ispecular = u_light.Ls * u_material.Ks * pow(max(dot(h, n), 0.0), u_material.Shininess);
        //<---
        return mix(
            Iambient + Idiffuse + Ispecular,
            vec3(0.5),
            0.5);
    }
}

void main(){
    gl_FragColor = vec4(ads(), 1.0);
}

