uniform sampler2D uf_Texture;

// UV Position
varying vec2 var_TextureUV;


void main()
{
//    vec4 color;
//    color = vec4( 0.8, 0.4, 0.8, 1.0 );
    vec4 color = texture2D( uf_Texture, var_TextureUV );
    gl_FragColor = color;
}