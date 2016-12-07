//
//// UV Position
//uniform sampler2D uf_Texture;
//varying vec2 var_TextureUV;
//varying vec4 var_Color;
//uniform vec3 textColor;
//
//void main()
//{
//    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(uf_Texture, var_TextureUV).r);
//    gl_FragColor = vec4(textColor, 1.0) * sampled;
//
////    vec4 sampled = vec4( 1.0, 1.0, 1.0, texture2D( uf_Texture, var_TextureUV ).r );
////    gl_FragColor = vec4( textColor, 1.0 ) * sampled;
////    gl_FragColor = texture2D( uf_Texture, var_TextureUV ) * vec4( textColor, 1.0 );
////    gl_FragColor = var_Color * texture2D( uf_Texture, var_TextureUV );
//    gl_FragColor = texture2D( uf_Texture, var_TextureUV );
//}

varying vec2 TexCoords;
//out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text, TexCoords).r);
    gl_FragColor = vec4(textColor, 1.0) * sampled;
}