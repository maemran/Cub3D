/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:29:20 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:30 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_max_width(t_vars *vars)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (vars->map[i])
	{
		len = ft_strlen(vars->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	vars->map_width = max;
}

static int	flood_from_player(t_vars *vars, int y, int x)
{
	int		row_len;
	char	tile;

	if (y < 0 || y >= vars->map_height)
		return (1);
	row_len = ft_strlen(vars->map[y]);
	if (x < 0 || x >= row_len)
		return (1);
	tile = vars->map[y][x];
	if (tile == ' ' || tile == '\0')
		return (1);
	if (tile == '1' || tile == '2')
		return (0);
	vars->map[y][x] = '2';
	if (flood_from_player(vars, y + 1, x))
		return (1);
	if (flood_from_player(vars, y - 1, x))
		return (1);
	if (flood_from_player(vars, y, x + 1))
		return (1);
	if (flood_from_player(vars, y, x - 1))
		return (1);
	return (0);
}

static int	flood_from_remaining_zero(t_vars *vars, int y, int x)
{
	int		row_len;
	char	tile;

	if (y < 0 || y >= vars->map_height)
		return (1);
	row_len = ft_strlen(vars->map[y]);
	if (x < 0 || x >= row_len)
		return (1);
	tile = vars->map[y][x];
	if (tile == ' ' || tile == '\0')
		return (1);
	if (tile == '1' || tile == '2')
		return (0);
	vars->map[y][x] = '2';
	if (flood_from_remaining_zero(vars, y + 1, x))
		return (1);
	if (flood_from_remaining_zero(vars, y - 1, x))
		return (1);
	if (flood_from_remaining_zero(vars, y, x + 1))
		return (1);
	if (flood_from_remaining_zero(vars, y, x - 1))
		return (1);
	return (0);
}

int	validate_map(t_vars *vars)
{
	int	start_x;
	int	start_y;
	int	y;
	int	x;

	start_x = (int)vars->xp_pos;
	start_y = (int)vars->yp_pos;
	if (flood_from_player(vars, start_y, start_x))
		return (1);
	y = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while ((size_t)x < ft_strlen(vars->map[y]))
		{
			if (vars->map[y][x] == '0')
			{
				if (flood_from_remaining_zero(vars, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	restore_map(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while ((size_t)x < ft_strlen(vars->map[y]))
		{
			if (vars->map[y][x] == '2')
				vars->map[y][x] = '0';
			x++;
		}
		y++;
	}
}
