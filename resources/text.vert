//// Attributes
//attribute vec2 in_Position;
//attribute vec2 in_TextureUV;
//attribute vec4 in_Color;
//
//// Texture
//varying vec2 var_TextureUV;
//varying vec4 var_Color;
//
//// Uniforms
uniform mat4 uf_Projection;
//
//void main()
//{
//    var_Color = in_Color;
//
//    // Texture UV coords
//    var_TextureUV = in_TextureUV;
//
//    // Vertex position
//    gl_Position = uf_Projection * vec4( in_Position.xy, 0.0, 1.0 );
//}

attribute vec4 vertex; // <vec2 pos, vec2 tex>
varying vec2 TexCoords;

void main()
{
    gl_Position = uf_Projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
