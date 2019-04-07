#include "scop.h"

unsigned 	WindowShouldClose(SDL_Event e)
{
	return (e.type == SDL_QUIT
		|| (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
		|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE));
}

unsigned	scop_error(const char *error)
{
	ft_putstr_fd(error, 2);
#if _MSC_VER
	if (IsDebuggerPresent())
		__debugbreak();
#else
	asm("int $3");
#endif 
	return -1;
}

void		GLClearError()
{
	while (glGetError());
}

char		GLCheckError(const char *Function, const char *File, int Line)
{
	(void)Function;
	(void)File;
	(void)Line;
	GLenum Error;
	while ((Error = glGetError()))
	{
#if _WIN32 || _WIN64
		__debugbreak();
#else
		continue;
#endif
	}
	return 1;
}

void			handle_rotations_and_scale(SDL_Event e, t_frame_info *frame, unsigned key_down)
{
	if (e.key.keysym.sym == 'h')
		frame->angles_offset.y = key_down ? -.5f : 0;
	else if (e.key.keysym.sym == 'l')
		frame->angles_offset.y = key_down ? .5f : 0;
	else if (e.key.keysym.sym == 'k')
		frame->angles_offset.x = key_down ? .5f : 0;
	else if (e.key.keysym.sym == 'j')
		frame->angles_offset.x = key_down ? -.5f : 0;
	else if (e.key.keysym.sym == '=')
		frame->scale_dir = key_down ? .05f : 0;
	else if (e.key.keysym.sym == '-')
		frame->scale_dir = key_down ? -.05f : 0;
}

void			handle_translation(SDL_Event e, t_frame_info *frame, unsigned key_down)
{
	if (e.key.keysym.sym == SDLK_PAGEUP)
		frame->position_offset.z = key_down ? .1 : 0;
	else if (e.key.keysym.sym == SDLK_PAGEDOWN)
		frame->position_offset.z = key_down ? -.1 : 0;
	else if (e.key.keysym.sym == SDLK_UP)
		frame->position_offset.y = key_down ? .1 : 0;
	else if (e.key.keysym.sym == SDLK_DOWN)
		frame->position_offset.y = key_down ? -.1 : 0;
	else if (e.key.keysym.sym == SDLK_RIGHT)
		frame->position_offset.x = key_down ? .1 : 0;
	else if (e.key.keysym.sym == SDLK_LEFT)
		frame->position_offset.x = key_down ? -.1 : 0;
}

unsigned		pre_draw(t_frame_info *frame)
{
	SDL_Event	e;

	frame->last_time = frame->current_time;
	frame->current_time = SDL_GetTicks();
	frame->delta_time = (frame->current_time - frame->last_time) / 1000.f;
	GLCall(glClearColor(0.0, 0.1, 0.01, 0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	while (SDL_PollEvent(&e))
	{
		if (WindowShouldClose(e))
			return 0;
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			handle_rotations_and_scale(e, frame, e.type == SDL_KEYDOWN);
			handle_translation(e, frame, e.type == SDL_KEYDOWN);
			if (e.key.keysym.sym == '1')
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else if (e.key.keysym.sym == '2')
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	return 1;
}

GLuint get_default_shader()
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
		
	if (frame->angles_offset.x || frame->angles_offset.y)
	{
		frame->angles += frame->angles_offset * frame->delta_time;
		glUniform2fv(glGetUniformLocation(program, "u_angles"), 1, &frame->angles);
	}
	if (frame->position_offset.x || frame->position_offset.y || frame->position_offset.z)
	{
		frame->position += frame->position_offset * frame->delta_time;
		glUniform3fv(glGetUniformLocation(program, "u_position"), 1, &frame->position);
	}
	if (frame->scale_dir)
	{
		frame->scale += frame->scale_dir * frame->delta_time;
		frame->scale = max(frame->scale, 0.001);
		glUniform1f(glGetUniformLocation(program, "u_scale"), frame->scale);
	}
	GLCall(glDrawArrays(GL_TRIANGLES, submesh->start, submesh->count));
}

void bind_buffers(t_buffer_pair model_buffers)
{
	GLCall(glBindVertexArray(model_buffers.vertex_array));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, model_buffers.vertex_buffer));
}

void		draw(t_frame_info *frame, t_model *model, t_skybox_data skybox)
{
	bind_buffers(model->buffers);
	ft_vec_for_each(&model->submeshes, draw_submesh, frame);
	
	bind_buffers(skybox.buffers);
	GLCall(glUseProgram(skybox.shader));
	GLCall(glUniform1i(glGetUniformLocation(skybox.shader, "skybox"), 0));
	GLCall(glUniform2fv(glGetUniformLocation(skybox.shader, "u_angles"), 1, &frame->angles));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.texture));
	GLCall(glDepthFunc(GL_LEQUAL));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	GLCall(glDepthFunc(GL_LESS));
}

int			event_loop(SDL_Window *window, t_model *model)
{
	t_frame_info	frame;
	t_skybox_data	skybox;
	GLuint			skybox_shader;

	ft_bzero(&frame, sizeof(t_frame_info));
	skybox.buffers = get_skybox_data();
	skybox.shader = get_skybox_shader();
	skybox.texture = create_texture_cube("res/skybox/");
	while (pre_draw(&frame))
	{
		if (!model->is_done)
			pthread_mutex_lock(&model->lock);
		if (model->is_dirty)
		{
			bind_buffers(model->buffers);
			GLCall(glBufferData(GL_ARRAY_BUFFER,
				model->vertecies.back * model->vertecies.size_of_type,
				model->vertecies.data, GL_DYNAMIC_DRAW));
		}
		draw(&frame, model, skybox);
		model->is_dirty = 0;
		if (!model->is_done)
			pthread_mutex_unlock(&model->lock);
		SDL_GL_SwapWindow(window);
	}
}