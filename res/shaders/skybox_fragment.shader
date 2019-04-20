
out vec4 FragColor;

in vec3 TexCoords;

layout(std140) uniform global
{
    mat4    mvp;
    mat4    light_view;
    vec3    LightDir;
}           g;

uniform samplerCube skybox;

void main()
{
	FragColor = texture(skybox, TexCoords);
}