/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:38:56 by joandre           #+#    #+#             */
/*   Updated: 2025/02/11 12:41:09 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_oper_draw_aux(t_other_data *data)
{
	if (data->step_x > 0)
		data->side_dist_x = (ceil(data->ray_x) - data->ray_x)
			* data->delta_dist_x;
	else
		data->side_dist_x = (data->ray_x - floor(data->ray_x))
			* data->delta_dist_x;
	if (data->step_y > 0)
		data->side_dist_y = (ceil(data->ray_y) - data->ray_y)
			* data->delta_dist_y;
	else
		data->side_dist_y = (data->ray_y - floor(data->ray_y))
			* data->delta_dist_y;
}

void	ft_oper_draw(t_other_data *data, float start_x, t_player *player)
{
	data->cos_angle = cos(start_x);
	data->sin_angle = sin(start_x);
	data->delta_dist_x = fabs(1 / data->cos_angle);
	data->delta_dist_y = fabs(1 / data->sin_angle);
	data->ray_x = player->x;
	data->ray_y = player->y;
	if (data->cos_angle > 0)
		data->step_x = 1;
	else
		data->step_x = -1;
	if (data->sin_angle > 0)
		data->step_y = 1;
	else
		data->step_y = -1;
	ft_oper_draw_aux(data);
}

void	hit_wall(t_other_data *data, int *hit_vertical)
{
	if (data->side_dist_x < data->side_dist_y)
	{
		data->ray_x += data->step_x;
		data->side_dist_x += data->delta_dist_x;
		*hit_vertical = 1;
	}
	else
	{
		data->ray_y += data->step_y;
		data->side_dist_y += data->delta_dist_y;
		*hit_vertical = 0;
	}
}

void	ft_define_color(t_other_data *data, t_game *game, int hit_vertical,
		int *color)
{
	(void)color;
	if (hit_vertical)
	{
		if (data->step_x > 0)
			data->color = game->texture->choose_color[0];
		else
			data->color = game->texture->choose_color[1];
	}
	else
	{
		if (data->step_y > 0)
			data->color = game->texture->choose_color[2];
		else
			data->color = game->texture->choose_color[3];
	}
}

int	ft_valid_map(char *name, t_game *mapp)
{
	int	i;
	i = 0;
	i = ft_strlen(name);
	mapp->full_map = ft_readmap((name));
	if (ft_strcmp(&name[i - 4], ".cub") == 0)
	{
		ft_analitic_map(mapp);
		return (1);
	}
	return (printf(RED "ERROR: file is not a \".cub\" type\n" RESET), exit(-1),
		0);
}
