
out vec4 FragColor;

in VS_OUT
{
    vec2 FragPos;
    vec2 TexCoord;
}        vs_out;

uniform sampler2D Texture;

void main() {
    vec3 Value = texture(Texture, vs_out.TexCoord).xxx;
    FragColor = vec4(Value, 1.0);
} 