#version 130

uniform float time;


void main()
{
	float adjTime = tan(time);
	vec2 position = gl_FragCoord.xy;
	vec4 color = vec4(1., 1., 1., 1.0);
	color.rb *= sin(dot(pow(adjTime, adjTime)*position,position))+1;
	gl_FragColor = color;
}
