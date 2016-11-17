// Attributes
attribute vec4 in_Position;
attribute vec4 in_TextureUV;

// Texture
varying vec2 var_TextureUV;

// Uniforms
uniform mat4 uf_Projection;

void main()
{
    // Texture UV coords
    var_TextureUV = vec2( in_Position.zw );

    // Vertex position
    gl_Position = uf_Projection * vec4( in_Position.xy, 0.0, 1.0 );
}
