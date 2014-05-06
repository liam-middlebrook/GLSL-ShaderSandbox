#version 130

uniform float time;

void main()
{
	vec2 position = gl_FragCoord.xy;

	vec4 color = vec4(1., 1., 1., 1.0);
	color.rb *= cos(time)+1;
	gl_FragColor = color;
	//*/
}
