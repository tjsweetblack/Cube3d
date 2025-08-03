/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-23 18:50:37 by joandre           #+#    #+#             */
/*   Updated: 2025-03-23 18:50:37 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1600
# define HEIGHT 920
# define BLOCK 54
# define DEBUG 0
# define RESET "\033[0m"
# define RED "\033[31m"

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_player
{
	float			x;
	float			y;
	int				end;
	float			dist;
	float			height;
	int				start_y;
	int				*pos;
	int				speed;
	float			angle;
	float			new_x;
	float			new_y;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
}					t_player;

typedef struct s_texture
{
	void			**img;
	void			*mlx_texture;
	char			**get_texture;
	int				**data;
	char			**get_color;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	int				*choose_color;
}					t_texture;

typedef struct s_other_data
{
	float			cos_angle;
	float			sin_angle;
	float			ray_x;
	float			ray_y;
	float			delta_dist_x;
	float			delta_dist_y;
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	int				hit_vertical;
	int				color;
	int				colory;
	int				tex_x;
	int				tex_y;
}					t_other_data;
typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	bool			*exit;
	char			*data;
	int				bpp;
	int				size_line;
	int				color_ceil;
	int				color_floor;
	int				endian;
	t_player		player;
	t_texture		*texture;
	t_other_data	*o_data;
	char			**map;
	char			**full_map;
}					t_game;

void				init_player(t_player *player, int *pos, char player_c);
int					key_release(int keycode, t_player *player);
int					key_press(int keycode, t_game *game);
void				move_player(t_player *player, t_game *game);
int					ft_valid_map(char *name, t_game *mapp);
int					ft_analizer_map(char **map);
void				ft_screen(t_game *game);
void				put_pixel(int x, int y, int color, t_game *game);
int					*ft_pos(t_game *game);
void				free_mtx(char **map);
void				free_mtx_int(int **mtx);
int					ft_return_angle(char c);
bool				touch(float px, float py, t_game *game);
void				ft_oper_draw(t_other_data *data, float start_x,
						t_player *player);
void				hit_wall(t_other_data *data, int *hit_vertical);
void				ft_define_color(t_other_data *data, t_game *game,
						int hit_vertical, int *color);
int					ft_convert_color(char *color, t_game *game);
void				load_texture(t_game *game);
float				fixed_dist(t_other_data *data, t_game *game);
void				ft_set_texture(t_game *game, t_other_data *data);
int					ft_opt_map(char c);
int					ft_top_down_map(char *map);
int					ft_body_map(char *map, char **full_map, int y);
void				ft_init_var_cal(t_player *player, t_game *game,
						t_other_data *data);
void				draw_line(t_player *player, t_game *game, float start_x,
						int i);
void				draw_map(t_game *game);
void				draw_square(int x, int y, int size, t_game *game);
void				clear_image(t_game *game);
void				free_mapp_extra(t_game *game);
void				free_mtx(char **map);
char				**ft_readmap(char *file);
int					ft_close_window(t_game *data);
void				free_all(t_game *game, int i);
int					ft_count_player(char **map);
void				free_textures(t_game *game);
void				ft_verify_space(t_game *game);
int					verify_conf_color(char *buffer);
int					ft_analitic_map(t_game *mapp);

#endif