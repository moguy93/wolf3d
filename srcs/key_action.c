/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 07:16:49 by moguy             #+#    #+#             */
/*   Updated: 2020/03/01 17:36:10 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void	go_right(t_env *env)
{
	env->cam.x += cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	env->cam.y -= sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	if (env->cam.x < 0 || env->cam.x >= env->map_width
			|| env->cam.y >= env->map_height || env->cam.y < 0
			|| env->map[(int)env->cam.x][(int)env->cam.y] != '0')
	{
		env->cam.x -= cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
		env->cam.y += sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	}
}

static inline void	go_left(t_env *env)
{
	env->cam.x -= cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	env->cam.y += sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	if (env->cam.x < 0 || env->cam.x >= env->map_width
			|| env->cam.y >= env->map_height || env->cam.y < 0
			|| env->map[(int)env->cam.x][(int)env->cam.y] != '0')
	{
		env->cam.x += cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
		env->cam.y -= sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	}
}

static inline void	go_up(t_env *env)
{
	env->cam.x += sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	env->cam.y += cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	if (env->cam.x < 0 || env->cam.x >= env->map_width
			|| env->cam.y >= env->map_height || env->cam.y < 0
			|| env->map[(int)env->cam.x][(int)env->cam.y] != '0')
	{
		env->cam.x -= sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
		env->cam.y -= cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	}
}

static inline void	go_down(t_env *env)
{
	env->cam.x -= sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	env->cam.y -= cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	if (env->cam.x < 0 || env->cam.x >= env->map_width
			|| env->cam.y >= env->map_height || env->cam.y < 0
			|| env->map[(int)env->cam.x][(int)env->cam.y] != '0')
	{
		env->cam.x += sinf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
		env->cam.y += cosf(env->cam.angle) * ((env->speed) ? 0.2f : 0.1f);
	}
}

void				key_action(t_env *env, int key[300])
{
	env->speed = (key[257]) ? true : false;
	if (key[53] == true)
		exit_red_cross((void*)env);
	if (key[123] == true)
		env->cam.angle -= 0.0393f;
	if (key[124] == true)
		env->cam.angle += 0.0393f;
	if (key[13] == true)
		go_up(env);
	if (key[1] == true)
		go_down(env);
	if (key[0] == true)
		go_left(env);
	if (key[2] == true)
		go_right(env);
	if (key[125] == true)
	{
		key[125] = false;
		env->cam.angle += 3.14159;
		threader((void*)env);
	}
	if (key[123] || key[124] || key[0] || key[1] || key[2] || key[13])
		threader((void*)env);
}
