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
	return 1;
}

t_bool		handle_mouse_buttons(SDL_MouseMotionEvent e, t_frame_info *frame)
{
	if (e.state & SDL_BUTTON_LMASK)
	{
		frame->angles.y += e.xrel / 180.f;
		frame->angles.x += e.yrel / 180.f;
	}
	else if (e.state & SDL_BUTTON_RMASK)
	{
		frame->light_angles.y -= e.xrel / 180.f;
		frame->light_angles.x += e.yrel / 180.f;
	}
}

t_bool	pre_draw(t_frame_info *frame)
{
	SDL_Event	e;

	frame->last_time = frame->current_time;
	frame->current_time = SDL_GetTicks();
	frame->delta_time = (frame->current_time - frame->last_time) / 1000.f;
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
		default_shader = compile_default_shader("res/shaders/uber_vertex.shader", "res/shaders/uber_fragment.shader");
	return default_shader;
}

static void draw_submesh(t_submesh *submesh, t_frame_info *frame)
{
	GLuint program;

	if (frame->is_depth_pass)
		program = frame->depth.shader;
	else if (submesh->shader_program)
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
	bind_buffers(model->buffers);
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, frame->depth.buffer));
	GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
	frame->is_depth_pass = 1;

	ft_vec_for_each(&model->submeshes, draw_submesh, frame);

	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	frame->is_depth_pass = 0;
	GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, frame->polygon_mode));
	draw_quad(frame, frame->depth_preview);
	bind_buffers(model->buffers);
	ft_vec_for_each(&model->submeshes, draw_submesh, frame);
	GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	//draw_quad(frame, model->skybox);
}

void prepare_frame_info(t_frame_info* frame)
{
	ft_bzero(frame, sizeof(t_frame_info));
	frame->depth = create_depth();
	frame->depth_preview.shader = compile_default_shader(
		"res/shaders/quad_vertex.shader", "res/shaders/quad_depth.shader");
	frame->depth_preview.texture = frame->depth.texture;
	frame->depth_preview.texture_type = GL_TEXTURE_2D;
	frame->polygon_mode = GL_FILL;
	frame->scale = 1;
	GLCALL(glGenBuffers(1, &frame->uniform_buffer));
	GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, frame->uniform_buffer));
	GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(t_m44),
		&frame->g_uniforms, GL_DYNAMIC_DRAW));
	GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, frame->uniform_buffer));
}

void calculate_shader_uniforms(t_frame_info* frame, t_model * model)
{
	t_float4 position;
	float scale;

	position = -model->offset_scale;
	scale = -position.w;
	position.w = 1;
	frame->g_uniforms.mvp = mult_matrix(mult_matrix(
		m_model(frame->angles, position, scale), m_identity()),
		m_identity());// frustum((t_float2) { 0.3, 0.3 }/*perspective_top_right(50, 1, .6f)*/, .6f, 3.5f));
	frame->g_uniforms.light_transform =
		m_model(frame->light_angles, position, scale);
	frame->g_uniforms.light_dir;// =
		mult_vec_matrix((t_float4) { 0, 0, -1 },
		mult_matrix(frame->g_uniforms.light_transform,
			m_model(frame->angles, position, scale)));
	GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(t_global_uniforms),
		&frame->g_uniforms, GL_DYNAMIC_DRAW));
}

int			event_loop(SDL_Window *window, t_model *model)
{
	t_frame_info	frame;

	prepare_frame_info(&frame);
	while (pre_draw(&frame))
	{
		calculate_shader_uniforms(&frame, model);
		pthread_mutex_lock(&model->lock);
		if (model->is_dirty)
		{
			bind_buffers(model->buffers);
			GLCALL(glBufferData(GL_ARRAY_BUFFER,
				model->vertecies.back * model->vertecies.size_of_type,
				model->vertecies.data, GL_STATIC_DRAW));
			model->is_dirty = 0;
		}
		draw(&frame, model);
		pthread_mutex_unlock(&model->lock);
		SDL_GL_SwapWindow(window);
	}
}