uniform float time;

float clamp(float _a, float _l, float _u) {
	if (_a <= _l) return _l;
	if (_a >= _u) return _u;
	return _a;
}

void main() {
	gl_FragColor = vec4(sin(time * .04f) + .2f, sin(time * .075f) + .2f, sin(time * .11f) + .2f, 1.f);
	gl_FragColor.a *= clamp(sin(time * 2.f + gl_FragCoord.x * .0025f) * .75f + 0.5f, 0.f, 1.f) * .25f;
	if (gl_FragCoord.y < 540.f) gl_FragColor.a *= (gl_FragCoord.y / 540.f) * (gl_FragCoord.y / 540.f);
	else gl_FragColor.a *= ((1080.f - gl_FragCoord.y) / 540.f) * ((1080.f - gl_FragCoord.y) / 540.f);
}