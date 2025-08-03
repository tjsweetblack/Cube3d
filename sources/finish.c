/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:10:56 by rquilami          #+#    #+#             */
/*   Updated: 2025/02/11 17:59:26 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_game *game)
{
	int	i;

	if (!game->texture)
		return ;
	i = -1;
	while (++i < 4)
	{
		if (game->texture->img[i])
			mlx_destroy_image(game->mlx, game->texture->img[i]);
	}
	free(game->texture->img);
	free(game->texture->choose_color);
	free(game->texture->get_color);
	free(game->texture->get_texture);
	free(game->texture->data);
	free(game->texture);
}

void	free_mtx(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_mapp_extra(t_game *game)
{
	free_mtx(game->full_map);
	free(game->texture->get_texture);
	free(game->texture->get_color);
	free(game->texture);
	exit(EXIT_FAILURE);
}

void	free_all(t_game *game, int i)
{
	int	j;

	if (!game->texture)
		return ;
	j = -1;
	while (++j < i)
	{
		if (game->texture->img[j])
			mlx_destroy_image(game->mlx, game->texture->img[j]);
	}
	free(game->texture->img);
	free(game->texture->choose_color);
	free(game->texture->data);
	free(game->texture->get_color);
	free(game->texture->get_texture);
	free(game->texture);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_mtx(game->full_map);
	exit(0);
}

// void freeze(t_game *game)
// {
// 	free(game->texture->img);
//     free(game->texture->choose_color);
//     free(game->texture->data);
//     free(game->texture);
// 	mlx_destroy_window(game->mlx, game->win);
// 	mlx_destroy_image(game->mlx, game->img);
// 	mlx_destroy_display(game->mlx);
// 	free(game->mlx);
// 	free_mtx(game->full_map);
// 	exit(0);
// }
