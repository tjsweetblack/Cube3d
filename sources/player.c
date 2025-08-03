/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:09:51 by rquilami          #+#    #+#             */
/*   Updated: 2025/02/10 15:53:56 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		ft_close_window(game);
	if (keycode == ESC)
		ft_close_window(game);
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move_ws(t_game *game, t_player *player, float cos_angle,
		float sin_angle)
{
	if (player->key_up)
	{
		player->new_x = player->x + cos_angle * player->speed;
		player->new_y = player->y + sin_angle * player->speed;
		if (!touch(player->new_x, player->new_y, game))
		{
			player->x = player->new_x;
			player->y = player->new_y;
		}
	}
	if (player->key_down)
	{
		player->new_x = player->x - cos_angle * player->speed;
		player->new_y = player->y - sin_angle * player->speed;
		if (!touch(player->new_x, player->new_y, game))
		{
			player->x = player->new_x;
			player->y = player->new_y;
		}
	}
}

void	move_ad(t_game *game, t_player *player, float cos_angle,
		float sin_angle)
{
	if (player->key_left)
	{
		player->new_x = player->x + sin_angle * player->speed;
		player->new_y = player->y - cos_angle * player->speed;
		if (!touch(player->new_x, player->new_y, game))
		{
			player->x = player->new_x;
			player->y = player->new_y;
		}
	}
	if (player->key_right)
	{
		player->new_x = player->x - sin_angle * player->speed;
		player->new_y = player->y + cos_angle * player->speed;
		if (!touch(player->new_x, player->new_y, game))
		{
			player->x = player->new_x;
			player->y = player->new_y;
		}
	}
}

void	move_player(t_player *player, t_game *game)
{
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	angle_speed = 0.03;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	move_ws(game, player, cos_angle, sin_angle);
	move_ad(game, player, cos_angle, sin_angle);
}
