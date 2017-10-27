uniform vec2 resolution;
uniform float time;
uniform float speed;
uniform vec3 a, b, c, d;
varying vec3 pos;

void main() {
    float r = length(resolution) / 2.0;
    vec2 o = resolution / 2.0;
    vec2 p = pos.xy + r - o - r;

    float t = length(p) / (r * 2.0) + time * speed;

    vec3 col = a + b * cos(6.2831852 * (c * t + d));

    gl_FragColor.rgba = vec4(col.rgb, 1.0);
}
