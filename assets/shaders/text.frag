uniform vec4 clr;
uniform float time;

void main() {
	gl_FragColor = clr;
	gl_FragColor.a *= sin(gl_FragCoord.y * 4.5f + 2.f * time) * .625f + .875f;
}