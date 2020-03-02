/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 03:45:24 by moguy             #+#    #+#             */
/*   Updated: 2020/03/01 16:25:58 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		error(char *err_msg, char *junk, t_env *env)
{
	if (junk)
		ft_memdel((void**)&junk);
	if (env)
		tab_del((void**)env->map, env->map_height);
	ft_putendl(err_msg);
	return (1);
}

int		exit_red_cross(void *env)
{
	mlx_destroy_image(((t_env*)env)->mlx->mlx, ((t_env*)env)->mlx->img);
	mlx_destroy_window(((t_env*)env)->mlx->mlx, ((t_env*)env)->mlx->win);
	tab_del((void**)((t_env*)env)->map, ((t_env*)env)->map_height);
	exit(EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	t_env		env;
	t_mlx		mlx;

	if (argc != 2)
		return (error(USAGE, NULL, NULL));
	ft_memset(&env, 0, sizeof(t_env));
	ft_memset(&mlx, 0, sizeof(t_mlx));
	if (get_map(argv[1], &env))
		return (1);
	if (init_mlx(&env, &mlx))
		return (error(MLX_ERR, NULL, &env));
	env.mlx = &mlx;
	threader(&env);
	mlx_hook(env.mlx->win, 2, 1L << 0, deal_key_press, &env);
	mlx_hook(env.mlx->win, 3, 1L << 1, deal_key_release, &env);
	mlx_loop_hook(env.mlx->mlx, deal_loop, &env);
	mlx_hook(env.mlx->win, 17, 1L << 17, exit_red_cross, &env);
	mlx_loop(env.mlx->mlx);
	return (0);
}
