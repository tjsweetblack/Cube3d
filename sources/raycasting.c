/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:19:12 by rquilami          #+#    #+#             */
/*   Updated: 2025/02/11 16:17:19 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_other_data *data, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = data->ray_x - game->player.x;
	delta_y = data->ray_y - game->player.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	return (game->map[y][x] == '1');
}
