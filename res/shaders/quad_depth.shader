
out vec4 FragColor;

in VS_OUT
{
    vec2 FragPos;
    vec2 TexCoord;
}        vs_out;

uniform sampler2D Texture;

void main() {
    vec3 Value = texture(Texture, vec2(vs_out.TexCoord.x, vs_out.TexCoord.y)).xxx;
    FragColor = vec4(Value, 1.0);
} 