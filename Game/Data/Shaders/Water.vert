#version 120
attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform mat4 u_WorldMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

varying vec2 v_UV;
varying float v_Height;

uniform vec3 u_RippleOrigin[4];
uniform float u_RippleRange[4];
uniform float u_Time;

void main()
{
	// Store object space position.
	vec4 objectpos = vec4(a_Position, 1);
	v_Height = 0;

	for(int i = 0; i < 4; i++)
	{
		float dist = distance(objectpos.xz, u_RippleOrigin[i].xz);

		if(dist < u_RippleRange[i])
		{
			float falloff = clamp(1 - dist/ u_RippleRange[i], 0.0, 1.0);
			float frequency = 0.2f;
			float amplitude = 2.0;

			float offset = sin(dist * frequency - u_Time * 5) * falloff;
			objectpos.y += offset * amplitude;

			v_Height += offset;
		}
	}

//				float quad = ((objectpos.x * objectpos.x) + (objectpos.z * objectpos.z));
//
//			float scale = 0.9f;
//			float frequency = 0.5f;
//			float speed = -6.0f;
//			float amplitude = 0.7f;
//
//			float val = scale * sin(u_Time * speed * frequency + quad);
//				
//			objectpos.y += val * amplitude;

	objectpos.y += sin(objectpos.x  + u_Time * 3) * 0.25f;
	objectpos.y += sin(objectpos.x  + u_Time * 3) * 0.25f;

	// Calculate world space position.
	vec4 worldpos = u_WorldMatrix * objectpos;

	// Calculate view space position.
	vec4 viewpos = u_ViewMatrix * worldpos;

	// Calculate clip space position.
	vec4 clippos = u_ProjectionMatrix * viewpos;

	// Store final position in gl_Position
    gl_Position = clippos;

	v_UV = a_UV;
}