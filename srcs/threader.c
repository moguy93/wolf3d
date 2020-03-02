/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:22:20 by moguy             #+#    #+#             */
/*   Updated: 2020/02/29 14:10:06 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	threader(void *env)
{
	int			i;

	i = -1;
	while (++i < MAX_THREADS)
		pthread_create(&(((t_env*)env)->thread[i]), NULL, &raycasting, env);
	i = -1;
	while (++i < MAX_THREADS)
		pthread_join(((t_env*)env)->thread[i], NULL);
	draw_mini_map((t_env*)env);
	mlx_put_image_to_window(((t_env*)env)->mlx->mlx, ((t_env*)env)->mlx->win,
			((t_env*)env)->mlx->img, 0, 0);
}

int		get_thread(pthread_t id, void *env)
{
	int		i;

	i = 0;
	while (i < MAX_THREADS && !pthread_equal(id, ((t_env*)env)->thread[i]))
		i++;
	return (i);
}
