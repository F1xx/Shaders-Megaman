#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform float u_Time;

varying vec2 v_UV;

void main()
{
	vec4 objectPos = vec4( a_Position, 1.0 );

    objectPos.y += sin( objectPos.x / 5.0 + u_Time ) * 1.0;
    objectPos.y -= sin( objectPos.z / 40.0 + u_Time ) * 2.0;

	vec4 worldPos = u_WorldMatrix * objectPos;
	vec4 viewPos = u_ViewMatrix * worldPos;
	vec4 clipPos = u_ProjectionMatrix * viewPos;

    gl_Position = clipPos;

    v_UV = a_UV;
}
