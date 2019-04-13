#include "scop.h"

unsigned 	WindowShouldClose(SDL_Event e)
{
	return (e.type == SDL_QUIT
		|| (e.type == SDL_WINDOWEVENT
		&& e.window.event == SDL_WINDOWEVENT_CLOSE)
		|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE));
}

unsigned	scop_error(const char *error)
{
	ft_putendl_fd(error, 2);
#if _MSC_VER
	if (IsDebuggerPresent())
		__debugbreak();
#else
	asm("int $3");
#endif 
	return -1;
}

void		gl_clear_error()
{
	while (glGetError());
}

char		gl_check_error(const char *function, const char *file, int line)
{
	(void)function;
	(void)file;
	(void)line;
	GLenum error;
	while ((error = glGetError()))
	{
#if _WIN32 || _WIN64
		__debugbreak();
#else
		continue;
#endif
	}
	return 1;
}

t_bool		handle_keyboard(SDL_Keycode sym, t_frame_info *frame, unsigned key_down)
{
	if (sym == 'h')
		frame->angles_offset.y = key_down ? -.5f : 0;
	else if (sym == 'l')
		frame->angles_offset.y = key_down ? .5f : 0;
	else if (sym == 'k')
		frame->angles_offset.x = key_down ? .5f : 0;
	else if (sym == 'j')
		frame->angles_offset.x = key_down ? -.5f : 0;
	else if (sym == '1')
		frame->polygon_mode = GL_FILL;
	else if (sym == '2')
		frame->polygon_mode = GL_LINE;
	else if (sym == '3')
		frame->polygon_mode = GL_POINT;
	else
		return 0;
	return 1;
}

t_bool		handle_mouse_buttons(SDL_MouseMotionEvent e, t_frame_info *frame)
{
	if (e.state & SDL_BUTTON_LMASK)
	{
		frame->angles.y += e.xrel / 180.f;
		frame->angles.x += e.yrel / 180.f;
	}
}

t_bool	pre_draw(t_frame_info *frame)
{
	SDL_Event	e;

	frame->last_time = frame->current_time;
	frame->current_time = SDL_GetTicks();
	frame->delta_time = (frame->current_time - frame->last_time) / 1000.f;
	GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
	while (SDL_PollEvent(&e))
	{
		if (WindowShouldClose(e))
			return 0;
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			handle_keyboard(e.key.keysym.sym, frame, e.type == SDL_KEYDOWN);
		else if (e.type == SDL_MOUSEMOTION)
			handle_mouse_buttons(e.motion, frame);
	}
	return 1;
}

GLuint		get_default_shader()
{
	static GLuint default_shader;

	if (default_shader == 0)
		default_shader = compile_default_shader();
	return default_shader;
}

static void draw_submesh(t_submesh *submesh, t_frame_info *frame)
{
	GLuint program;

	program = submesh->shader_program ? submesh->shader_program : get_default_shader();
	glUseProgram(program);
	GLCALL(glDrawArrays(GL_TRIANGLES, submesh->start, submesh->count));
}

void		bind_buffers(t_buffers model_buffers)
{
	GLCALL(glBindVertexArray(model_buffers.vertex_array));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, model_buffers.vertex_buffer));
}

void		draw(t_frame_info *frame, t_model *model)
{
	if (frame->angles_offset.x || frame->angles_offset.y)
		frame->angles += frame->angles_offset * frame->delta_time;
	if (frame->position_offset.x || frame->position_offset.y || frame->position_offset.z)
		frame->position += frame->position_offset * frame->delta_time;
	if (frame->scale_dir)
	{
		frame->scale += frame->scale_dir * frame->delta_time;
		frame->scale = max(frame->scale, 0.001);
	}
	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, frame->polygon_mode));
	bind_buffers(model->buffers);
	ft_vec_for_each(&model->submeshes, draw_submesh, frame);
	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	draw_skybox(frame, model);
}

int			event_loop(SDL_Window *window, t_model *model)
{
	t_frame_info	frame;

	ft_bzero(&frame, sizeof(t_frame_info));
	frame.polygon_mode = GL_FILL;
	GLCALL(glGenBuffers(1, &frame.uniform_buffer));
	GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, frame.uniform_buffer));
	GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(t_m44), &frame.g_uniforms, GL_DYNAMIC_DRAW));
	GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, frame.uniform_buffer));
	frame.scale = 1;
	while (pre_draw(&frame))
	{
		frame.g_uniforms.light_dir = normalize(mult_vec_matrix((t_float4) { 1, 1, 1, 0 }, frame.g_uniforms.mvp));
		GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(t_global_uniforms), &frame.g_uniforms, GL_DYNAMIC_DRAW));
		pthread_mutex_lock(&model->lock);
		if (model->is_dirty)
		{
			bind_buffers(model->buffers);
			GLCALL(glBufferData(GL_ARRAY_BUFFER,
				model->vertecies.back * model->vertecies.size_of_type,
				model->vertecies.data, GL_STATIC_DRAW));
			model->is_dirty = 0;
		}
		t_float4 position = -model->offset_scale;
		float scale = -position.w;
		position.w = 1;
		t_float2 angles = { 1, 1 };
		frame.g_uniforms.mvp = //m_model(angles, position, scale);
		mult_matrix(
			mult_matrix(
				m_model(frame.angles, position, scale),
				m_world()
			),
			frustum(perspective_top_right(50, 1, .6f), .6f, 3.5f)
		);
		draw(&frame, model);
		pthread_mutex_unlock(&model->lock);
		SDL_GL_SwapWindow(window);
	}
}