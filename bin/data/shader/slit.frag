uniform sampler2DRect image;
uniform vec2 resolution;
uniform float rand, rand1, rand2, rand3, rand4;
uniform float time;
uniform float value;
varying vec3 pos;

void main() {
    float v = value + 1.0;
    vec2 tex = vec2(1.0 + floor(pos.x / v / rand1) * v * rand1, pos.y);
    vec4 col = texture2DRect(image, tex);

    gl_FragColor.rgba = col.rgba;
}
