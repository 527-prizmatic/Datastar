uniform vec4 clr;
uniform float time;

void main() {
	gl_FragColor = clr;
	gl_FragColor.a *= sin(gl_FragCoord.y * 2.f + 3.f * time) * .75f + .75f;
}