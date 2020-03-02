/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 02:34:01 by moguy             #+#    #+#             */
/*   Updated: 2020/02/26 07:46:45 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_pixel(t_env *env, int color, int x, int y)
{
	int		pos;

	pos = (y * ((t_env*)env)->scr_width + x) * 4;
	((t_env*)env)->mlx->data[pos] = (char)(color >> 16 & 255);
	((t_env*)env)->mlx->data[pos + 1] = (char)(color >> 8 & 255);
	((t_env*)env)->mlx->data[pos + 2] = (char)(color & 255);
}
