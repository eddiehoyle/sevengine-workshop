
// UV Position
uniform sampler2D uf_Texture;
varying vec2 var_TextureUV;
varying vec4 var_Color;

void main()
{

    gl_FragColor = var_Color * texture2D( uf_Texture, var_TextureUV );
//    gl_FragColor = texture2D( uf_Texture, var_TextureUV );
}