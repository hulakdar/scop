
#include "scop.h"

unsigned	scop_error(const char *error)
{
	ft_putendl_fd(error, 2);
	DEBUG_BREAK();
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
		DEBUG_BREAK();
	}
	return 1;
}