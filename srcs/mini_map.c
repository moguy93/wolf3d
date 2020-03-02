/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:02:13 by moguy             #+#    #+#             */
/*   Updated: 2020/03/01 16:35:31 by moguy            ###   ########.fr       */
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
	int		tmp[2];
	int		size2;

	y = -MINIMAP_SIZE4;
	size2 = MINIMAP_SIZE4 * MINIMAP_SIZE4 + MINIMAP_SIZE4 * 0.8f;
	while (y <= MINIMAP_SIZE4)
	{
		tmp[0] = y * y;
		tmp[1] = (int)(env->cam.y * MINIMAP_SIZE);
		x = -MINIMAP_SIZE4;
		while (x <= MINIMAP_SIZE4)
		{
			if (x * x + tmp[0] <= size2)
				fill_pixel(env, 0xDD, tmp[1] + x,
						(int)(env->cam.x * MINIMAP_SIZE + y));
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
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
		tmp = y + y_start;
		while (++x < MINIMAP_SIZE)
		{
			fill_pixel(env, color, x_start + x, tmp);
		}
	}
}

void				draw_mini_map(t_env *env)
{
	int		x;
	int		y;
	int		color;

	y = -1;
	while (++y < env->map_height)
	{
		x = -1;
		while (++x < env->map_width)
		{
			color = minimap_color(env, x, y);
			draw_square(env, x * MINIMAP_SIZE, y * MINIMAP_SIZE, color);
		}
	}
	draw_circle(env);
}
