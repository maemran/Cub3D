/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:03:18 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:12 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_last_line(t_vars *vars, t_parsing *parsing)
{
	int	i;
	int	j;
	int	last_line;

	i = 0;
	j = 0;
	last_line = 0;
	while (vars->map[i])
	{
		j = 0;
		if (vars->map[i][j] == '1' && is_this_map(parsing, i))
		{
			last_line = i;
		}
		i++;
	}
	return (last_line);
}

static void	check_top_wall(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int	j;

	j = 0;
	while (vars->map[0][j] && vars->map[0][j] != '\n')
	{
		if (vars->map[0][j] == ' ' || vars->map[0][j] == '\t'
			|| vars->map[0][j] == '1')
			j++;
		else
		{
			write(2, "Error\nthe map not surrounded by walls on top", 45);
			free_all_and_exit(parsing, vars, directions);
		}
	}
}

void	check_walls(t_parsing *parsing, t_vars *vars, t_directions *directions)
{
	int	final_line;

	get_max_width(vars);
	check_taps(parsing, vars, directions);
	final_line = get_last_line(vars, parsing);
	check_top_wall(parsing, vars, directions);
	check_walls_two(parsing, vars, directions);
	(void)final_line;
}
