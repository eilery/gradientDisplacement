uniform sampler2DRect image;
uniform float rand, rand1, rand2, rand3, rand4;
uniform float value;
varying vec3 pos;

void main() {
    vec2 tex = vec2(pos.x, pos.y);
    vec2 cut = vec2(floor(sin(pos.y / rand4 - rand * value)) * pow(value * rand1, 1.2) * rand, 0);
    vec4 col = texture2DRect(image, tex + cut);

	gl_FragColor.rgba = col.rgba;
}
