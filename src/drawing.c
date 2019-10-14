/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:49:31 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/14 00:45:58 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "shaders.h"

void		new_material(const char *line, t_obj *obj)
{
	t_material material;

	ft_bzero(&material, sizeof(t_material));
	material.name = ft_strdup(line);
	obj->current_material =
		(t_material*)ft_vec_pushback(&obj->result->materials, &material);
}

GLuint		get_default_shader(void)
{
	static GLuint default_shader;

	if (default_shader == 0)
		default_shader = compile_default_shader(
			"res/shaders/uber_vertex.shader",
			"res/shaders/uber_fragment.shader");
	return (default_shader);
}

static void	draw_submesh(t_submesh *submesh, t_frame_info *frame)
{
	GLuint program;

	(void)frame;
	if (submesh->shader_program)
	{
		program = submesh->shader_program;
	}
	else if (submesh->material)
	{
		if (submesh->material->diffuse_tex_name)
		{
			submesh->material->diffuse_tex = create_texture_2d(submesh->material->diffuse_tex_name);
			submesh->material->diffuse_tex_name = NULL;
			submesh->material->has_texture = 1;
		}
		submesh->shader_program = generate_shader(submesh->material);
		program = submesh->shader_program;
	}
	else
		program = get_default_shader();
	GLCALL(glUseProgram(program));
	if (submesh->material && submesh->material->has_texture)
	{
		GLCALL(glActiveTexture(GL_TEXTURE2));
		GLCALL(glBindTexture(GL_TEXTURE_2D, submesh->material->diffuse_tex));
	}
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
	ft_vec_for_each(&model->submeshes,
			(t_for_each_predicate)draw_submesh, frame);
	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	draw_quad(model->skybox);
}
