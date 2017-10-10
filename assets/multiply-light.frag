uniform sampler2D texture;
uniform sampler2D lightmap;

void main()
{
	vec2 coord = gl_TexCoord[0].xy;
	coord.y = 1.0 - coord.y;
	vec4 lightcol = texture2D(lightmap, coord);
	vec4 texcol = texture2D(texture, coord);

	gl_FragColor = texcol * lightcol;
}
