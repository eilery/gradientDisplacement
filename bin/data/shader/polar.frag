uniform vec2 resolution;
uniform float time;
uniform float speed;
uniform vec3 a, b, c, d;
varying vec3 pos;

void main() {
    vec2 o = resolution / 2.0;
    vec2 p = pos.xy - o;

    float t = degrees(atan(p.x, p.y)) / 180.0 + time * speed;

    vec3 col = a + b * cos(6.2831852 * (c * t + d));

    gl_FragColor.rgba = vec4(col.rgb, 1.0);
}
