
#include "GL/glew.h"
#include "scop.h"

static GLuint	create_skybox_shader()
{
	t_vector	defines;
	char		*line;
	GLuint		result;

	ft_vec_init(&defines, sizeof(char *), 32);
	line = "#version 440\n";
	ft_vec_pushback(&defines, &line);
	result = compile_shaders("res/shaders/skybox_vertex.shader", "res/shaders/skybox_fragment.shader", defines);
	ft_vec_del(&defines);
	return result;
}

t_buffer_pair	create_skybox_data()
{
	static const float	skyboxVertices[] = { -1.f, 1.f, -1.f, -1.f, -1.f, -1.f,
	1.f, -1.f, -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, -1.f, -1.f, 1.f, -1.f, -1.f, -1.f,
	1.f, -1.f, -1.f, -1.f, -1.f, 1.f, -1.f, -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, -1.f,
	-1.f, 1.f, 1.f, -1.f, -1.f, 1.f, -1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
	1.f, -1.f, 1.f, -1.f, -1.f, -1.f, -1.f, 1.f, -1.f, 1.f, 1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f, -1.f, 1.f, -1.f, -1.f, 1.f, -1.f, 1.f, -1.f, 1.f, 1.f,
	-1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f, -1.f, -1.f,
	-1.f, -1.f, -1.f, -1.f, 1.f, 1.f, -1.f, -1.f, 1.f, -1.f, -1.f, -1.f, -1.f,
	1.f, 1.f, -1.f, 1.f };
	t_buffer_pair	skybox;

	GLCall(glGenVertexArrays(1, &skybox.vertex_array));
	GLCall(glGenBuffers(1, &skybox.vertex_buffer));
	GLCall(glBindVertexArray(skybox.vertex_array));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, skybox.vertex_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER,
		sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
									3 * sizeof(float), (GLvoid *)0));
	return skybox;
}

GLuint			get_skybox_shader()
{
	static GLuint skybox_shader;

	if (!skybox_shader)
		skybox_shader = create_skybox_shader();
	return skybox_shader;
}
