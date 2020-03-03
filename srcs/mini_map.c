/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:02:13 by moguy             #+#    #+#             */
/*   Updated: 2020/03/03 18:05:31 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline int	minimap_color(t_env *env, int x, int y)
{
	if (env->map[y][x] == '1')
		return (0xFFFFFF);
	else
		return (0x888888);
}

static inline void	draw_circle(t_env *env)
{
	int		x;
	int		y;
	int		tmp[3];
	int		size2;

	y = -env->mini_circle;
	size2 = env->mini_circle * env->mini_circle + env->mini_circle * 0.8f;
	tmp[1] = (int)(env->cam.x * env->minimap_size);
	tmp[2] = (int)(env->cam.y * env->minimap_size);
	while (y <= env->mini_circle)
	{
		tmp[0] = y * y;
		x = -env->mini_circle;
		while (x <= env->mini_circle)
		{
			if ((x * x) + tmp[0] <= size2)
				fill_pixel(env, 0xDD,tmp[2] + x, tmp[1] + y);
			x++;
		}
		y++;
	}
}

static inline void	draw_square(t_env *env, int x_start, int y_start, int color)
{
	int		x;
	int		y;
	int		tmp;

	y = -1;
	while (++y < env->minimap_size)
	{
		x = -1;
		tmp = y + y_start;
		while (++x < env->minimap_size)
		{
			fill_pixel(env, color, x_start + x, tmp);
		}
	}
}

void				draw_mini_map(t_env *env)
{
	int		x;
	int		y;
	int		y2;
	int		color;

	y = -1;
	while (++y < env->map_height)
	{
		y2 = y * env->minimap_size;
		x = -1;
		while (++x < env->map_width)
		{
			color = minimap_color(env, x, y);
			draw_square(env, x * env->minimap_size, y2, color);
		}
	}
	draw_circle(env);
}
