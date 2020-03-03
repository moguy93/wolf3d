/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 02:34:01 by moguy             #+#    #+#             */
/*   Updated: 2020/03/02 17:12:05 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_pixel(t_env *env, int color, int x, int y)
{
	int		pos;

	pos = (y * SCR_W + x) * 4;
	if (pos < 0 || pos > SCR_T)
		return ;
	((t_env*)env)->mlx->data[pos] = (char)(color >> 16 & 255);
	((t_env*)env)->mlx->data[pos + 1] = (char)(color >> 8 & 255);
	((t_env*)env)->mlx->data[pos + 2] = (char)(color & 255);
}
