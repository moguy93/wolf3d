/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 01:40:49 by moguy             #+#    #+#             */
/*   Updated: 2020/03/02 17:36:43 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdbool.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define USAGE "./wolf3d file"
# define MLX_ERR "MLX ERROR"

# define SCR_W 1080
# define SCR_H 720
# define SCR_T 3110400
# define MIN_MAP_W 1
# define MIN_MAP_H 1
# define MAX_MAP_W 150
# define MAX_MAP_H 150
# define EPSILON 0.005f
# define DEPTH 20.0f
# define FLOOR 0x000088
# define MAX_THREADS 8

typedef enum		e_sprite_id
{
	SP_MIN,
	SP_WARNING,
	SP_BLACKWALL,
	SP_BLUE,
	SP_CELL,
	SP_MAX
}					t_sprite_id;

typedef struct		s_sprite
{
	void			*img;
	char			*data;
	int				height;
	int				width;
}					t_sprite;

typedef struct		s_cam
{
	float			x;
	float			y;
	float			fov;
	float			fov2;
	float			fov3;
	float			angle;
	float			eye_x;
	float			eye_y;
	float			ftest_x;
	float			ftest_y;
	float			t_angle;
	float			sample_x;
	int				floor;
	int				ceiling;
	int				test_x;
	int				test_y;
	int				sprite;
	bool			hitw;
}					t_cam;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				siz;
	int				end;
	int				bpp;
}					t_mlx;

typedef struct		s_env
{
	t_sprite		sprites[SP_MAX];
	t_mlx			*mlx;
	char			**map;
	pthread_t		thread[MAX_THREADS];
	t_cam			cam;
	int				scr_width_thread;
	float			scr_height2;
	int				minimap_size;
	int				mini_circle;
	int				map_width;
	int				map_height;
	int				cam_x;
	int				cam_y;
	bool			speed;
	int				key[300];
}					t_env;

int					color_ceiling(t_env *env, int y);
int					color_floor(t_env *env, int y);
int					deal_key_press(int key, void *env);
int					deal_key_release(int key, void *env);
int					deal_loop(void *env);
int					deal_move(int x, int y, void *env);
void				draw_line(t_env *env, int coord1[6], int x_end, int y_end);
void				draw_mini_map(t_env *env);
int					error(char *err_msg, char *junk, t_env *env);
char				*err_singleton(int error);
int					exit_red_cross(void *env);
void				fill_pixel(t_env *env, int color, int x, int y);
int					get_map(char *av, t_env *env);
int					get_thread(pthread_t id, void *env);
void				init_map(t_env *env);
int					init_mlx(t_env *env, t_mlx *mlx);
int					init_sprites(t_env *env, t_mlx *mlx);
void				key_action(t_env *env, int key[300]);
void				*raycasting(void *env);
int					sample_color(t_env *env, t_cam *cam, int y, float dist);
char				*sprite_singleton(int index);
void				tab_del(void **tab, int size);
void				threader(void *env);

#endif
