/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 02:00:56 by moguy             #+#    #+#             */
/*   Updated: 2020/03/03 18:22:15 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		init_sprites(t_env *env, t_mlx *mlx)
{
	int			i;
	int			blank;

	i = 0;
	while (++i < SP_MAX)
	{
		if (!(env->sprites[i].img = mlx_xpm_file_to_image(mlx->mlx,
					sprite_singleton(i), &env->sprites[i].width,
					&env->sprites[i].height)))
			return (1);
		if (!(env->sprites[i].data = mlx_get_data_addr(env->sprites[i].img,
						&blank, &blank, &blank)))
			return (1);
	}
	return (0);
}

void	init_map(t_env *env)
{
	env->cam.x = (float)env->cam_y + 0.5f;
	env->cam.y = (float)env->cam_x + 0.5f;
	env->cam.fov = 3.14159f * 0.25f;
	env->cam.fov2 = env->cam.fov * 0.5f;
	env->cam.fov3 = 3.14159f * 0.75F;
	env->cam.angle = -3.14159 * 0.5f;
	env->scr_height2 = (float)SCR_H * 0.5f;
	env->scr_width_thread = SCR_W / MAX_THREADS;
	env->minimap_size = (int)(10.0f * (1.0f - (
					(env->map_height > env->map_width) ? (
						(float)env->map_height / (float)MAX_MAP_H) : (
						(float)env->map_width / (float)MAX_MAP_W))));
	env->mini_circle = (int)(4.0f * (1.0f - (
					(env->map_height > env->map_width) ? (
						(float)env->map_height / (float)MAX_MAP_H) : (
						(float)env->map_width / (float)MAX_MAP_W))));
	if (env->minimap_size == 0)
		env->minimap_size = 2;
	if (env->mini_circle == 0)
		env->mini_circle = 1;
}

int		init_mlx(t_env *env, t_mlx *mlx)
{
	if (!(mlx->mlx = mlx_init()))
		return (1);
	if (!(mlx->win = mlx_new_window(mlx->mlx, SCR_W, SCR_H, "Wolf3D")))
		return (1);
	mlx->img = mlx_new_image(mlx->mlx, SCR_W, SCR_H);
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->siz, &mlx->end);
	init_map(env);
	if (init_sprites(env, mlx))
		return (1);
	return (0);
}
