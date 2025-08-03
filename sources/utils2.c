/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:33:48 by rquilami          #+#    #+#             */
/*   Updated: 2025/02/11 14:00:11 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_convert_color(char *color, t_game *game)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	if (!color)
	{
		(ft_putstr_fd(RED "Error\nThere are not elements in the map" RESET, 2),
			free_mtx(game->full_map));
		(free(game->texture->get_color), free(game->texture->get_texture));
		free(game->texture);
		exit(EXIT_FAILURE);
	}
	if (verify_conf_color(color))
	{
		(ft_putstr_fd(RED "Error\nThe configuration of color is wrong\n" RESET,
				2), free_mtx(game->full_map));
		(free(game->texture->get_color), free(game->texture->get_texture));
		(free(game->texture), exit(EXIT_FAILURE));
	}
	rgb = ft_split(&color[2], ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	return (free_mtx(rgb), (r << 16 | g << 8 | b));
}

void	ft_replace(char **s, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < n && s[j])
	{
		i = 0;
		while (s[j][i])
		{
			if (s[j][i] == '\n')
			{
				s[j][i] = '\0';
				break ;
			}
			i++;
		}
		j++;
	}
}

void	load_texture(t_game *game)
{
	int	i;

	ft_replace(game->texture->get_texture, 4);
	game->texture->img = (malloc(sizeof(void *) * 4));
	if (!game->texture)
		return (ft_putstr_fd("Erro ao alocar memória para textura", 2),
			exit(-1));
	game->texture->choose_color = malloc(sizeof(int *) * 4);
	game->texture->data = malloc(sizeof(int *) * 4);
	if (!game->texture->choose_color || !game->texture->data)
		return (ft_putstr_fd("Erro ao alocar memória para texturas", 2),
			exit(-1));
	i = -1;
	while (++i < 4)
	{
		game->texture->img[i] = mlx_xpm_file_to_image(game->mlx,
				game->texture->get_texture[i], &game->texture->width,
				&game->texture->height);
		if (!game->texture->img[i])
			(ft_putstr_fd(RED "Erro\n ao carregar a textura\n" RESET, 2),
				free_all(game, i), exit(-1));
		game->texture->data[i] = (int *)mlx_get_data_addr(game->texture->img[i],
				&game->texture->bpp, &game->texture->size_line,
				&game->texture->endian);
	}
}

void	ft_set_texture(t_game *game, t_other_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture->choose_color[i] = game->texture->data[i][(int)data->tex_y
			* game->texture->width + data->tex_x];
		i++;
	}
}

void	ft_init_var_cal(t_player *player, t_game *game, t_other_data *data)
{
	int	speed;

	speed = 0;
	player->dist = fixed_dist(data, game);
	speed = 5 * (player->dist / 150);
	if (speed < 5)
		speed = 5;
	if (player->dist > 100 && player->dist < 150)
		player->speed = 5;
	else
		player->speed = speed;
	player->height = (BLOCK / player->dist) * (WIDTH / 2);
	player->start_y = (HEIGHT - player->height) / 2;
	player->end = player->start_y + player->height;
}
