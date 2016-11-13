// Attributes
attribute vec4 in_Position;

// Uniforms
uniform mat4 uf_Projection;

void main()
{
    // Vertex position
    gl_Position = uf_Projection * vec4( in_Position.xy, 0.0, 1.0 );
}
