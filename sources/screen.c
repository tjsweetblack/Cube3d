/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:43:31 by joandre           #+#    #+#             */
/*   Updated: 2025/02/11 09:29:05 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_screen(t_game *game)
{
	int	x;
	int	y;
	int	color;

	color = game->color_ceil;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, color, game);
			x++;
		}
		if (y < HEIGHT / 2)
			color = game->color_floor;
		y++;
	}
}
