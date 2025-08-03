/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:20:40 by rquilami          #+#    #+#             */
/*   Updated: 2025/02/07 10:22:34 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(x, y, game->color_ceil, game);
			else
				put_pixel(x, y, game->color_floor, game);
			x++;
		}
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_other_data	data;
	int				hit_vertical;
	int				y;

	ft_oper_draw(&data, start_x, player);
	while (!touch(data.ray_x, data.ray_y, game))
		hit_wall(&data, &hit_vertical);
	ft_init_var_cal(player, game, &data);
	y = player->start_y;
	if (hit_vertical)
		data.tex_x = (int)((data.ray_y / game->texture->width)
				* game->texture->width) % game->texture->width;
	else
		data.tex_x = (int)((data.ray_x / game->texture->width)
				* game->texture->width) % game->texture->width;
	while (y < player->end)
	{
		data.tex_y = (int)((y - player->start_y) / player->height
				* game->texture->height);
		ft_set_texture(game, &data);
		ft_define_color(&data, game, hit_vertical, game->texture->choose_color);
		put_pixel(i, y, data.color, game);
		y++;
	}
}
