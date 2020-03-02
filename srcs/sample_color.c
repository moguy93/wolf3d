/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:08:22 by moguy             #+#    #+#             */
/*   Updated: 2020/03/01 17:01:11 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		color_ceiling(t_env *env, int y)
{
	int		color;
	float	tmp;

	tmp = 1.0f - ((float)y / env->scr_height2);
	color = (int)((float)FLOOR * tmp);
	return (color);
}

int		color_floor(t_env *env, int y)
{
	int		color;
	float	tmp;

	tmp = (((float)y - env->scr_height2) / env->scr_height2);
	color = (int)((float)FLOOR * tmp);
	return (color);
}

int		sample_color(t_env *env, t_cam *c, int y, float dist)
{
	int		color;
	int		index[3];
	float	sample_y;
	float	shade;

	color = 0;
	shade = 1.0f - dist / (float)DEPTH;
	sample_y = ((float)y - (float)c->ceiling) / (
			(float)c->floor - (float)c->ceiling);
	index[0] = (int)(c->sample_x * (float)env->sprites[c->sprite].width);
	index[1] = (int)(sample_y * (float)env->sprites[c->sprite].height - 1);
	if (index[1] < 0)
		index[1] = 0;
	index[2] = (index[1] * env->sprites[c->sprite].width + index[0]) * 4;
	color = (int)((float)(
				env->sprites[c->sprite].data[index[2]] & 255) * shade);
	color <<= 8;
	color |= (int)((float)(
				env->sprites[c->sprite].data[index[2] + 1] & 255) * shade);
	color <<= 8;
	color |= (int)((float)(
				env->sprites[c->sprite].data[index[2] + 2] & 255) * shade);
	return (color);
}
