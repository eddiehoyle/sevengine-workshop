
// UV Position
varying vec2 var_TextureUV;
uniform sampler2D uf_Texture;

void main()
{
    gl_FragColor = texture2D( uf_Texture, var_TextureUV );
//    gl_FragColor = vec4( var_TextureUV.xy, 0, 1 );
}