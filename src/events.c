#include "scop.h"

char WindowShouldClose(const SDL_Event* e)
{
	return ( e->type == SDL_QUIT
		|| (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_CLOSE)
		|| (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE) );
}

char scop_error(const char *error)
{
	ft_putstr_fd(error, 2);
#if  _WIN32 || _WIN64
	__debugbreak();
#endif 
	return -1;
}

void GLClearError()
{
	while (glGetError());
}

char GLCheckError(const char *Function, const char *File, int Line)
{
	GLenum Error;
	while (Error = glGetError())
	{
		__debugbreak();
	}
	return 1;
}

