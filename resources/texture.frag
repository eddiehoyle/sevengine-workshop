
// UV Position
uniform sampler2D uf_Texture;
varying vec2 var_TextureUV;

void main()
{
//    vec4 color = vec4( 0.0, 0.0, 1.0, 1.0 );

    gl_FragColor = texture2D( uf_Texture, var_TextureUV );
//    gl_FragColor = vec4( var_TextureUV.xy, 0, 1 );
}