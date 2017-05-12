#version 150
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 color;
in vec2 texcoord;

uniform sampler2DRect tex;
uniform float time;
uniform float t[4];
uniform float size;

out vec4 vColor;

const float PI = 3.14159265358979323;

void main() {

    vec4 th = texture(tex, texcoord);

    float rad = 2.0 * PI * (th.x + th.y * t[1]);

    mat4 rot = mat4(
        cos(rad), 0.0, sin(rad), 0.0,
        0.0, 1.0, 0.0,  0.0,
        -sin(rad), 0.0, cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    mat4 trans = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        180.0 * t[0], 80.0 * (th.z * t[2] * 0.5 + th.w * t[3]), 0.0, 1.0
    );

    vec3 v = vec3(2.0 * sin(time*position.x), 2.0 * cos(time*position.y), 2.0 * sin(time*position.z));
    vec4 p = rot * trans * vec4((position.xyz + v) * size, 1.0);
    vColor = color;

    gl_Position = modelViewProjectionMatrix * p;
    gl_PointSize = 500.0 / gl_Position.w;
}
