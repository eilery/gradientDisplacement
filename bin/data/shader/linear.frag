uniform vec2 resolution;
uniform float time;
uniform float speed;
uniform vec3 a, b, c, d;
varying vec3 pos;

void main() {
    float r = length(resolution) / 2.0;
    vec2 o = resolution / 2.0;
    vec2 p = pos.xy + r - o - r;

    p.x = p.x * cos(time * 4.0 * speed) - p.y * sin(time * 4.0 * speed);
    p.y = p.x * sin(time * 4.0 * speed) + p.y * cos(time * 4.0 * speed);

    vec2 t = p / (r * 2.0);
    vec3 col = a + b * cos(6.2831852 * (c * t.x + d));

    gl_FragColor.rgba = vec4(col.rgb, 1.0);
}
