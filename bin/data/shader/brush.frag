uniform sampler2DRect image;
uniform sampler2DRect brush;
uniform sampler2DRect mask;
varying vec3 pos;

void main() {
    vec4 col1 = texture2DRect(image, pos.xy);
    vec4 col2 = texture2DRect(brush, pos.xy);
    vec4 col3 = texture2DRect(mask, pos.xy);

    gl_FragColor.rgba = vec4(col1.rgb * (1.0 - col3.a) + col2.rgb * col3.a, 1.0);
}
