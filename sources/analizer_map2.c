/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analizer_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:56:13 by rquilami          #+#    #+#             */
/*   Updated: 2025/02/11 16:59:18 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_tab_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_opt_map(char c)
{
	const char	*string = "NSEW";

	return (ft_strchr(string, c) != NULL);
}

int	ft_top_down_map(char *map)
{
	int	j;

	j = 0;
	if (!map)
		return (-1);
	while (ft_tab_space(map[j]))
		j++;
	if (map[j] != '1')
		return (-1);
	while (map[j] && map[j] != '\n')
	{
		if (map[j] != '1' && map[j] != ' ')
			return (-1);
		j++;
	}
	return (0);
}

int	verify_map(char *map, char **full_map, int y, int x)
{
	while (map[x] && map[x] != '\n')
	{
		if (map[x] == '0')
		{
			if (ft_tab_space(full_map[y - 1][x] || ft_tab_space(full_map[y
						- 1][x] == '\n')) || ft_tab_space(full_map[y + 1][x]
					|| ft_tab_space(full_map[y + 1][x] == '\n')) || full_map[y
				- 1][x] == '\n' || full_map[y + 1][x] == '\n'
				|| ft_tab_space(full_map[y][x + 1]))
				return (-1);
		}
		else if (ft_tab_space(map[x]) && map[x + 1] == '0')
			return (-1);
		if (map[x] != '1' && map[x] != '0' && !ft_tab_space(map[x])
			&& !ft_opt_map(map[x]))
			return (-1);
		if (map[x] != '1' && map[x + 1] == '\n')
			return (-1);
		x++;
	}
	return (0);
}

int	ft_body_map(char *map, char **full_map, int y)
{
	int	x;

	x = 0;
	if (!map || !full_map)
		return (-1);
	while (map[x] && ft_tab_space(map[x]))
		x++;
	if (map[x] != '1')
		return (-1);
	if (verify_map(map, full_map, y, x) == -1)
		return (-1);
	return (0);
}
