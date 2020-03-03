/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 03:15:43 by moguy             #+#    #+#             */
/*   Updated: 2020/03/03 16:57:13 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void	draw_column(t_env *env, t_cam *c, int x_s,
		float dist_to_wal)
{
	int		y;
	int		color;

	y = -1;
	c->ceiling = (int)(env->scr_height2 - (float)SCR_H / dist_to_wal);
	c->floor = SCR_H - c->ceiling;
	while (++y < SCR_H)
	{
		if (y < c->ceiling)
			color = color_ceiling(env, y);
		else if (y >= c->ceiling && y <= c->floor)
		{
			if (dist_to_wal >= DEPTH)
				color = 0;
			else
				color = sample_color(env, c, y, dist_to_wal);
		}
		else
			color = color_floor(env, y);
		fill_pixel(env, color, x_s, y);
	}
}

static inline void	has_hit(t_cam *cam, float *dist_to_wall)
{
	float	dist;

	dist = *dist_to_wall;
	cam->hitw = true;
	cam->ftest_x = cam->x + cam->eye_x * dist;
	cam->ftest_y = cam->y + cam->eye_y * dist;
	cam->t_angle = atan2f((cam->ftest_y - ((float)cam->test_y + 0.5f)),
			(cam->ftest_x - ((float)cam->test_x + 0.5f)));
	if (cam->t_angle >= -(cam->fov) && cam->t_angle < cam->fov
			&& (cam->sprite = SP_WARNING))
		cam->sample_x = cam->ftest_y - (float)cam->test_y;
	else if (cam->t_angle >= cam->fov && cam->t_angle < cam->fov3
			&& (cam->sprite = SP_BLACKWALL))
		cam->sample_x = cam->ftest_x - (float)cam->test_x;
	else if (cam->t_angle < -(cam->fov) && cam->t_angle >= -(cam->fov3)
			&& (cam->sprite = SP_BLUE))
		cam->sample_x = cam->ftest_x - (float)cam->test_x;
	else if ((cam->t_angle >= cam->fov3 || cam->t_angle < -(cam->fov3))
			&& (cam->sprite = SP_CELL))
		cam->sample_x = cam->ftest_y - (float)cam->test_y;
	if ((cam->test_x == 0 && cam->sprite == SP_CELL)
			|| (cam->test_y == 0 && cam->sprite == SP_BLUE))
		dist = DEPTH;
	*dist_to_wall = dist;
}

static inline void	hit_wall_loop(t_env *env, t_cam *cam, float *dist_to_wall)
{
	float	dist;

	dist = *dist_to_wall;
	dist += EPSILON;
	cam->test_x = (int)(cam->x + cam->eye_x * dist);
	cam->test_y = (int)(cam->y + cam->eye_y * dist);
	if (cam->test_x < 0 || cam->test_x >= env->map_height
			|| cam->test_y < 0 || cam->test_y >= env->map_width)
	{
		dist = DEPTH;
		cam->hitw = true;
	}
	else
	{
		if (env->map[cam->test_x][cam->test_y] == '1')
			has_hit(cam, &dist);
	}
	*dist_to_wall = dist;
}

static inline void	raycasting_loop(t_env *env, t_cam *c, int x_s, int x_e)
{
	float	ray_angle;
	float	dist_to_wall;

	while (x_s < x_e && x_s < SCR_W)
	{
		ray_angle = (c->angle - c->fov2) + (
				((float)x_s / (float)SCR_W) * c->fov);
		dist_to_wall = 0;
		c->hitw = false;
		c->eye_x = sinf(ray_angle);
		c->eye_y = cosf(ray_angle);
		while (!c->hitw && dist_to_wall < DEPTH)
			hit_wall_loop(env, c, &dist_to_wall);
		draw_column(env, c, x_s, dist_to_wall);
		x_s++;
	}
}

void				*raycasting(void *env)
{
	int		x_start;
	int		x_end;
	t_cam	c;

	c.x = ((t_env*)env)->cam.x;
	c.y = ((t_env*)env)->cam.y;
	c.fov = ((t_env*)env)->cam.fov;
	c.fov2 = ((t_env*)env)->cam.fov2;
	c.fov3 = ((t_env*)env)->cam.fov3;
	c.angle = ((t_env*)env)->cam.angle;
	x_start = ((t_env*)env)->scr_width_thread * get_thread(pthread_self(), env);
	x_end = x_start + ((t_env*)env)->scr_width_thread;
	raycasting_loop((t_env*)env, &c, x_start, x_end);
	return (NULL);
}
