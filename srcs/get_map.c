/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 05:13:53 by moguy             #+#    #+#             */
/*   Updated: 2020/03/03 18:25:45 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline int	check_map(t_env *env)
{
	int		i;
	int		j;

	i = -1;
	while (++i < env->map_height && env->map[i])
	{
		j = 0;
		while (env->map[i][j])
		{
			if (env->map[i][j] != '0' && env->map[i][j] != '1')
				return (1);
			j++;
		}
		if (j != env->map_width)
			return (1);
	}
	return (0);
}

static inline int	get_map_value(int fd, t_env *env, char *line)
{
	int		i;
	int		ret;

	i = -1;
	ret = -1;
	while (++i < env->map_height)
	{
		if ((ret = get_next_line(fd, &line)) < 0)
			return (error(err_singleton(0), NULL, NULL));
		if (ret == 0)
			break ;
		if (line && !(env->map[i] = ft_strdup(line)))
			return (error(err_singleton(0), NULL, NULL));
		ft_memdel((void**)&line);
	}
	if (i < env->map_height || (ret = get_next_line(fd, &line)) != 0)
	{
		if (ret > 0)
			ft_memdel((void**)&line);
		return (error(err_singleton(0), NULL, NULL));
	}
	close(fd);
	if (check_map(env))
		return (error(err_singleton(1), NULL, NULL));
	return (0);
}

static inline int	get_info(int fd, char *line, t_env *env)
{
	if (get_next_line(fd, &line) <= 0
			|| (env->map_width = (int)ft_atoi(line)) < MIN_MAP_W
			|| env->map_width > MAX_MAP_W)
		return (1);
	ft_memdel((void**)&line);
	if (get_next_line(fd, &line) <= 0
			|| (env->map_height = (int)ft_atoi(line)) < MIN_MAP_H
			|| env->map_height > MAX_MAP_H)
		return (1);
	ft_memdel((void**)&line);
	if (get_next_line(fd, &line) <= 0
			|| (env->cam_x = (int)ft_atoi(line)) < 0
			|| env->cam_x >= env->map_width)
		return (1);
	ft_memdel((void**)&line);
	if (get_next_line(fd, &line) <= 0
			|| (env->cam_y = (int)ft_atoi(line)) < 0
			|| env->cam_y >= env->map_height)
		return (1);
	ft_memdel((void**)&line);
	return (0);
}

int					get_map(char *av, t_env *env)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(av, O_RDONLY);
	if (fd < 0 || fd > 4864)
		return (error(USAGE, line, NULL));
	if (get_info(fd, line, env))
		return (error(err_singleton(0), line, NULL));
	if (!(env->map = (char**)malloc(
					sizeof(char*) * (unsigned int)env->map_height + 1)))
		return (error(err_singleton(0), NULL, NULL));
	if (get_map_value(fd, env, line))
		return (1);
	if (env->map[env->cam_y][env->cam_x] == '1')
		return (error(err_singleton(0), line, NULL));
	return (0);
}
