/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:31:19 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 22:33:36 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "obj.h"

void	gl_clear_error();
char	gl_check_error(const char *function, const char *file, int fine);

void	bind_buffers(t_buffers model_buffers);
void	event_loop(SDL_Window *window, t_model *model);

#endif
