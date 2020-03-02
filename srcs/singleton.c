/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:03:17 by moguy             #+#    #+#             */
/*   Updated: 2020/03/01 19:17:10 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*err_singleton(int error)
{
	static char	msg_err[2][400];

	if (msg_err[0][0] == 0)
	{
		ft_strcpy(&msg_err[0][0], "The file has to contain :\n\n-Screen width, \
must be between 100 and 1920\n-Screen height, must be between 100 and 1080\n\
-Map width, must be between 1 and 1000\n-Map height, must be between 1 and 1000\
\nPosition start of your player in the map, he mustn't start within a wall, \
he will begin at the center of the cell :\n-Pos_x\n-Pos_y\n-The map");
		ft_strcpy(&msg_err[1][0], "The map must be without spaces, only \
numbers : 0 or 1 (1 for a wall).");
	}
	return (&msg_err[error][0]);
}

char	*sprite_singleton(int index)
{
	static char	*path[SP_MAX] = {
				"blank",
				"resources/sprites/Black7.XPM",
				"resources/sprites/Black5.XPM",
				"resources/sprites/Blue5.XPM",
				"resources/sprites/Orange12.XPM"};

	return (&path[index][0]);
}
