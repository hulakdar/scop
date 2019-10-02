
#include "scop.h"

GLuint		get_default_shader()
{
	static GLuint default_shader;

	if (default_shader == 0)
		default_shader = compile_default_shader(
			"res/shaders/uber_vertex.shader",
			"res/shaders/uber_fragment.shader");
	return default_shader;
}

void apply_material(t_material material)
{
	
}

static void draw_submesh(t_submesh *submesh, t_frame_info *frame)
{
	GLuint program;

	if (submesh->shader_program)
		program = submesh->shader_program;
	else
		program = get_default_shader();
	GLCALL(glUseProgram(program));
	GLCALL(glDrawArrays(GL_TRIANGLES, submesh->start, submesh->count));
}

void		bind_buffers(t_buffers model_buffers)
{
	GLCALL(glBindVertexArray(model_buffers.vertex_array));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, model_buffers.vertex_buffer));
}

void		draw(t_frame_info *frame, t_model *model)
{
	GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
	bind_buffers(model->buffers);
	ft_vec_for_each(&model->submeshes, (t_for_each_predicate)draw_submesh, frame);
	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	draw_quad(model->skybox);
}
