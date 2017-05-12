#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 color;
in vec2 texcoord;

uniform sampler2DRect uTex;
uniform int uLevs[3];
uniform vec3 uParams;
uniform float t;

out vec3 vColor;

mat4 trs[3];
vec4 theta;

const float PI = 3.14159265358979323;

mat4 x90 = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(PI/4), sin(PI/4), 0.0,
        0.0, -sin(PI/4), cos(PI/4), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

mat4 createTRS(int i){

    float rad = PI * 2.0 * theta[i];
    float scale = 4.0 * pow(1.5, - i) * uParams[i];

    mat4 t = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, scale, 0.0, 1.0
    );
    mat4 r = mat4(
        cos(rad), sin(rad), 0.0, 0.0,
        -sin(rad), cos(rad), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    return x90 * r * t;

}

void main() {

    theta = texture(uTex, texcoord);

    for (int i = 0; i < 3; i++) {
        trs[i] = createTRS(uLevs[i]);
    }
    float r = 2.0;
    vec4 v = vec4(r * sin(t*position.x), r * cos(t*position.y), r * sin(t*position.z), 0.0);
    vec4 p = trs[0] * trs[1] * trs[2] * (position + v);
    vColor = color.rgb;
    gl_Position = modelViewProjectionMatrix * p;
    gl_PointSize = 500.0 / gl_Position.w;
}
