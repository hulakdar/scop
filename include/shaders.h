/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:39:13 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:16:42 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H

# include "libft.h"
# include "scop.h"
# include "GL/glew.h"

typedef struct	s_shader_code
{
	t_vector	lines;
	t_vector	lengths;
}				t_shader_code;

GLint			compile_shaders(char *vertex_path,
								char *fragment_path,
								t_vector defines);
GLuint			compile_default_shader(char *vert, char *frag);
GLuint			get_skybox_shader(void);
t_material		get_default_material(void);
GLuint			generate_shader(t_material *mat);

#endif
