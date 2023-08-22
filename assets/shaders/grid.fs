#version 330 core

in vec2 outTexCoord;

out vec4 outColor;

uniform vec3 eye;

float square(vec2 p,vec2 b){
	vec2 d = abs(p) - b;
	return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

void main()
{
	vec2 p = 2.0*outTexCoord-1.0;
	p *=eye.z;
	p += eye.xy;
	vec2 pf = 2.0*fract(p) - 1.0;
	vec3 col = vec3(smoothstep(1.0,0.3,square(pf,vec2(0.6))));
	outColor = vec4(col,1.0);
}