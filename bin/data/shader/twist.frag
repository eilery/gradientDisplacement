uniform sampler2DRect image;
uniform vec2 resolution;
uniform float rand, rand1, rand2, rand3;
uniform float time;
uniform float value;
varying vec3 pos;

void main() {
    vec2 tex1 = vec2(
      //min(resolution.x, pos.x + sin(pos.y / 153.25 + rand1 * rand + time * 2.0) * rand2 * 20.0 / rand),
      //min(resolution.y, pos.y + cos(pos.x / 251.57 + rand2 * rand + time * 0.2) * rand1 * 80.0 / rand));
      min(resolution.x, pos.x + sin(pos.y / 153.25 + rand1 * rand + time * 2.0) * rand2 * 20.0 / rand * pow(value / 127.0, 5.0)),
      min(resolution.y, pos.y + cos(pos.x / 251.57 + rand2 * rand + time * 0.2) * rand1 * 80.0 / rand * pow(value / 127.0, 5.0)));
    vec2 tex2 = vec2(max(16.0, tex1.x), max(16.0, tex1.y));

    vec4 col = texture2DRect(image, tex2);
    gl_FragColor.rgba = col.rgba;
}
