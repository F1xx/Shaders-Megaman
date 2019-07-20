#version 120

uniform sampler2D u_Texture;

varying vec2 v_UV;
varying float v_Height;

void main()
{
	vec4 color = texture2D( u_Texture, v_UV );

	color.xy *= v_Height;

	gl_FragColor = color;
}
