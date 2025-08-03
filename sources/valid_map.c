/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:00:19 by joandre           #+#    #+#             */
/*   Updated: 2025/02/11 17:59:35 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_txt_color(t_game *game, int k)
{
	static int	i;
	static int	j;

	if (ft_strncmp(game->full_map[k], "NO", 2) == 0)
		i++;
	else if (ft_strncmp(game->full_map[k], "SO", 2) == 0)
		i++;
	else if (ft_strncmp(game->full_map[k], "WE", 2) == 0)
		i++;
	else if (ft_strncmp(game->full_map[k], "EA", 2) == 0)
		i++;
	else if (ft_strncmp(game->full_map[k], "F", 1) == 0)
		j++;
	else if (ft_strncmp(game->full_map[k], "C", 1) == 0)
		j++;
	if (i > 4)
		return (ft_putstr_fd(RED "ERROR\nRepetitive texture\n" RESET, 2), 0);
	else if (j > 2)
		return (ft_putstr_fd(RED "ERROR\nRepetitive color\n" RESET, 2), 0);
	return (1);
}

int	ft_complete(t_game *game, int k)
{
	if (ft_strncmp(game->full_map[k], "NO", 2) == 0)
		game->texture->get_texture[0] = &game->full_map[k][3];
	else if (ft_strncmp(game->full_map[k], "SO", 2) == 0)
		game->texture->get_texture[1] = &game->full_map[k][3];
	else if (ft_strncmp(game->full_map[k], "WE", 2) == 0)
		game->texture->get_texture[2] = &game->full_map[k][3];
	else if (ft_strncmp(game->full_map[k], "EA", 2) == 0)
		game->texture->get_texture[3] = &game->full_map[k][3];
	else if (ft_strncmp(game->full_map[k], "F", 1) == 0)
		game->texture->get_color[0] = game->full_map[k];
	else if (ft_strncmp(game->full_map[k], "C", 1) == 0)
		game->texture->get_color[1] = game->full_map[k];
	else if ((game->full_map[k][0]) != '1' && (game->full_map[k][0]) != '\n')
		return (ft_putstr_fd(RED "Error\nMap's file configuration is wrong\n"
				RESET, 2), 0);
	if (check_txt_color(game, k) == 0)
		return (0);
	return (1);
}

int	verify_conf_color(char *buffer)
{
	int	i;
	int	sep;

	sep = 0;
	i = 0;
	if (buffer[i + 1] && buffer[i + 1] != ' ')
		return (1);
	i += 2;
	while (buffer[i] && buffer[i] != ' ')
	{
		if ((!ft_isdigit(buffer[i]) && buffer[i] != ',' && buffer[i] != '\n')
			|| (buffer[i] == ',' && !ft_isdigit(buffer[i + 1])))
			return (1);
		if (buffer[i] == ',' && ft_isdigit(buffer[i + 1]))
			sep++;
		i++;
	}
	if (sep == 2)
		return (0);
	else
		return (1);
}

int	ft_verify_options_in_map(t_game *game)
{
	int	i;

	i = 0;
	game->texture = malloc(sizeof(t_texture));
	game->texture->get_texture = malloc(sizeof(char *) * 4);
	game->texture->get_texture[0] = "NULL";
	game->texture->get_texture[1] = "NULL";
	game->texture->get_texture[2] = "NULL";
	game->texture->get_texture[3] = "NULL";
	game->texture->get_color = malloc(sizeof(char *) * 2);
	game->texture->get_color[0] = "NULL";
	game->texture->get_color[0] = "NULL";
	game->texture->get_color[1] = "NULL";
	game->texture->get_color[1] = "NULL";
	while (game->full_map[i] && game->full_map[i][0] != '1'
		&& game->full_map[i][0] != ' ' && game->full_map[i][0] != '\t')
	{
		if (!ft_complete(game, i))
			(free_mtx(game->full_map), free(game->texture->get_texture),
				free(game->texture->get_color), free(game->texture),
				exit(EXIT_FAILURE));
		i++;
	}
	return (i);
}

int	ft_analitic_map(t_game *mapp)
{
	int	i;

	i = 0;
	i = ft_verify_options_in_map(mapp);
	mapp->color_ceil = ft_convert_color(mapp->texture->get_color[0], mapp);
	mapp->color_floor = ft_convert_color(mapp->texture->get_color[1], mapp);
	while (mapp->full_map[i] && mapp->full_map[i][0] == '\n')
		i++;
	mapp->map = &mapp->full_map[i];
	if (!mapp->map[0])
	{
		ft_putstr_fd(RED "ERROR\nThe file map is empty\n" RESET, 2);
		free_mapp_extra(mapp);
	}
	if (ft_count_player(&mapp->full_map[i]) == -1)
		free_mapp_extra(mapp);
	if (ft_analizer_map(&mapp->full_map[i]))
	{
		printf(RED "Error\nIvalid map\n" RESET);
		free_mapp_extra(mapp);
	}
	ft_verify_space(mapp);
	return (i);
}
