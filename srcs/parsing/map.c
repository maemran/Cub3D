/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:04:54 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:03 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_non_player_char(char c)
{
	return (c == '1' || c == '0' || c == ' ');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

static void	handle_player(t_vars *vars, int i, int j, int *count)
{
	vars->facing_dir = vars->map[i][j];
	vars->xp_pos = j + 0.5;
	vars->yp_pos = i + 0.5;
	(*count)++;
}

static int	validate_map_char(t_vars *vars, int i, int j, int *count)
{
	char	c;

	c = vars->map[i][j];
	if (is_valid_non_player_char(c))
		return (0);
	else if (is_player_char(c))
	{
		handle_player(vars, i, j, count);
		return (0);
	}
	return (-1);
}

void	check_elements(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (validate_map_char(vars, i, j, &count) < 0)
			{
				write(2, "Error\nundefined element inside the map\n", 40);
				free_all_and_exit(parsing, vars, directions);
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		print_and_free(parsing, vars, directions,
			"Error\nthere is no player or more than one player\n");
	if (validate_map(vars))
		print_and_free(parsing, vars, directions, "Error\ninvalid path");
}
