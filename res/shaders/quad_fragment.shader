
out vec4 FragColor;

in VS_OUT
{
    vec2 FragPos;
    vec2 TexCoord;
}        vs_out;

uniform sampler2D Texture;

void main() {
    vec4 Value = texture(Texture, vs_out.TexCoord);
    FragColor = vec4(Value.xyz, 1.0);
} 