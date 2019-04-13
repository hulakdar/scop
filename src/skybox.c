
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
	result = compile_shaders(
		"res/shaders/skybox_vertex.shader",
		"res/shaders/skybox_fragment.shader",
		defines);
	ft_vec_del(&defines);
	return result;
}

t_buffers	create_skybox_data()
{
	const float	quad[] = {
		-1.f, 1.f,
		-1.f, -1.f,
		1.f, -1.f,
		1.f, -1.f,
		1.f, 1.f,
		-1.f, 1.f
	};
	t_buffers	skybox;

	GLCALL(glGenVertexArrays(1, &skybox.vertex_array));
	GLCALL(glGenBuffers(1, &skybox.vertex_buffer));
	GLCALL(glBindVertexArray(skybox.vertex_array));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, skybox.vertex_buffer));
	GLCALL(glBufferData(GL_ARRAY_BUFFER,
		sizeof(quad), quad, GL_STATIC_DRAW));
	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
									2 * sizeof(float), (GLvoid *)0));
	return skybox;
}

GLuint			get_skybox_shader()
{
	static GLuint skybox_shader;

	if (!skybox_shader)
		skybox_shader = create_skybox_shader();
	return skybox_shader;
}


void			draw_skybox(t_frame_info *frame, t_model *model)
{
	bind_buffers(model->skybox.buffers);
	GLCALL(glUseProgram(model->skybox.shader));
	GLCALL(glActiveTexture(GL_TEXTURE0));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, model->skybox.texture));
	GLCALL(glDepthFunc(GL_LEQUAL));
	GLCALL(glDrawArrays(GL_TRIANGLES, 0, 6));
	GLCALL(glDepthFunc(GL_LESS));
}
	
