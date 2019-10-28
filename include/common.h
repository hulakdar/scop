/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:39:09 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/19 17:39:23 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"
# include <pthread.h>
# include <stdint.h>

# define CONTEXT_PROFILE SDL_GL_CONTEXT_PROFILE_CORE
# define CONTEXT_FLAGS SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
# define SDL_MAIN_HANDLED

# define GLEW_STATIC
# include <GL/glew.h>
# if _WIN32 || _WIN64 || __WIN32__
#  include <SDL.h>
#  include <SDL_image.h>
# else
#  include <SDL2/SDL.h>
# endif

#endif
