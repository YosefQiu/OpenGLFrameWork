#version 330
layout (lines) in;                              // now we can access 2 vertices
layout (triangle_strip, max_vertices = 4) out;  // always (for now) producing 2 triangles (so 4 vertices)
uniform vec4  u_viewportSize;
uniform vec4 u_thickness = vec4(4.0f, 1.0f, 1.0f, 1.0f);
void main()
{
    vec4 p1 = gl_in[0].gl_Position;
    vec4 p2 = gl_in[1].gl_Position;
    float lineWidth = u_thickness.x;
    vec2 dir    = normalize((p2.xy/p2.w - p1.xy/p1.w) * u_viewportSize.xy);
    vec2 offset = vec2(-dir.y, dir.x) * lineWidth / u_viewportSize.xy;
    gl_Position = p1 + vec4(offset.xy * p1.w, 0.0, 0.0);
    EmitVertex();
    gl_Position = p1 - vec4(offset.xy * p1.w, 0.0, 0.0);
    EmitVertex();
    gl_Position = p2 + vec4(offset.xy * p2.w, 0.0, 0.0);
    EmitVertex();
    gl_Position = p2 - vec4(offset.xy * p2.w, 0.0, 0.0);
    EmitVertex();
    EndPrimitive();
}
