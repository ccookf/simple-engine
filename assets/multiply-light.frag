uniform sampler2D texture;
uniform sampler2D lightmap;
uniform float strength;

void main()
{
	vec4 lightcol = texture2D(lightmap, gl_TexCoord[0].xy);
	vec4 texcol = texture2D(texture, gl_TexCoord[0].xy);

	gl_FragColor = texcol * lightmap * strength;
}
