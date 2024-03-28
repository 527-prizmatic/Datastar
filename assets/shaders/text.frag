uniform vec4 clr;
uniform float time;

void main() {
	gl_FragColor = clr;
//	gl_FragColor.a *= sin(gl_FragCoord.y * 1.f + 2.f * time) * .5f + .75f;
}