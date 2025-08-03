/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analizer_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-05 14:18:36 by joandre           #+#    #+#             */
/*   Updated: 2025-04-05 14:18:36 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_c_matrix(char **mat)
{
	int	i;

	if (!mat)
		return (0);
	i = 0;
	while (mat[i])
		i++;
	return (i);
}

int	ft_count_player(char **map)
{
	int	x;
	int	y;
	int	count_player;

	count_player = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (ft_opt_map(map[y][x]))
			{
				count_player++;
				if (count_player > 1)
					return (ft_putstr_fd(RED "ERROR: More player in the map\n"
							RESET, 2), -1);
			}
			x++;
		}
		y++;
	}
	if (count_player == 0)
		return (ft_putstr_fd(RED "ERROR: no player in the map\n"RESET, 2), -1);
	return (0);
}

int	ft_analizer_intr(char **map, int total_lines)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (y == 0 || y == total_lines - 1)
		{
			if (ft_top_down_map(map[y]) == -1)
				return (-1);
		}
		else
		{
			if (ft_body_map(map[y], map, y) == -1)
				return (-1);
		}
		y++;
	}
	return (0);
}

int	ft_analizer_map(char **map)
{
	int	total_lines;

	if (!map)
		return (-1);
	total_lines = ft_c_matrix(map);
	if (!total_lines)
		return (1);
	if (!ft_strchr(map[total_lines - 1], '1'))
		return (1);
	if (ft_analizer_intr(map, total_lines) == -1)
		return (1);
	return (0);
}

void	ft_verify_space(t_game *game)
{
	int	*pos;
	int	y;
	int	x;

	pos = ft_pos(game);
	y = pos[1];
	x = pos[0];
	free(pos);
	if (game->map[y][x + 1] == ' ' || game->map[y][x + 1] == '\t'
		|| game->map[y][x - 1] == ' ' || game->map[y][x - 1] == '\t')
	{
		printf(RED "ERROR\nAround of the player has space or tab\n" RESET);
		exit(EXIT_FAILURE);
	}
	if (game->map[y + 1][x] == ' ' || game->map[y + 1][x] == '\t' || game->map[y
		- 1][x] == ' ' || game->map[y - 1][x] == '\t')
	{
		printf(RED "ERROR\nAround of the player has space or tab\n" RESET);
		exit(EXIT_FAILURE);
	}
}
