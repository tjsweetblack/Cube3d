/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:09:40 by rquilami          #+#    #+#             */
/*   Updated: 2025/02/11 12:15:19 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_close_window(t_game *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	free_textures(data);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_mtx(data->full_map);
	exit(0);
	return (0);
}

void	init_player(t_player *player, int *pos, char player_c)
{
	int	num;

	num = ft_return_angle(player_c);
	player->x = (pos[0] + 0.5) * BLOCK;
	player->y = (pos[1] + 0.5) * BLOCK;
	player->angle = num * (M_PI / 180.0);
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	free(pos);
}

void	init_game(t_game *game)
{
	int		*pos;
	char	player;

	pos = ft_pos(game);
	player = game->map[pos[1]][pos[0]];
	init_player(&game->player, pos, player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	load_texture(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, game);
		draw_map(game);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 2)
		return (0);
	if (!ft_valid_map(av[1], &game))
		return (1);
	init_game(&game);
	mlx_hook(game.win, 17, 0, ft_close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
