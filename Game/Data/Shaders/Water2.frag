#version 120

uniform sampler2D u_Texture;
uniform float u_Time;

varying vec2 v_UV;

void main()
{
    vec2 newUV = v_UV;
    newUV.x += sin( u_Time + v_UV.y * 10.0 ) * 0.08;
    newUV.y -= sin( u_Time + v_UV.x * 15.0 ) * 0.12;

    vec4 color1 = texture2D( u_Texture, newUV + u_Time / 20.0 );
    vec4 color2 = texture2D( u_Texture, newUV + vec2( u_Time / 21.0, 0.0 ) );

    color1 += vec4( 15.0/255.0, 103.0/255.0, 227.0/255.0, 0.0 );

    vec4 color = color1 - color2 * 0.13;

    gl_FragColor = color;
}
