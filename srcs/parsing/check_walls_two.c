/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:04:00 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:10 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_row_start(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		i;
	int		j;
	char	first_char;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j] != '\n' && vars->map[i][j])
		{
			if (vars->map[i][j] != ' ' && vars->map[i][j] != '\t')
			{
				first_char = vars->map[i][j];
				if (first_char != '1')
				{
					write(2, "Error\nnot surrounded by walls first\n", 37);
					free_all_and_exit(parsing, vars, directions);
				}
				break ;
			}
			j++;
		}
		i++;
	}
}

static void	check_row_end(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		i;
	int		j;
	char	last_char;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j] != '\n' && vars->map[i][j])
			j++;
		j--;
		while (j >= 0 && (vars->map[i][j] == ' ' || vars->map[i][j] == '\t'))
			j--;
		if (j >= 0)
		{
			last_char = vars->map[i][j];
			if (last_char != '1')
			{
				write(2, "Error\nnot surrounded by walls last\n", 36);
				free_all_and_exit(parsing, vars, directions);
			}
		}
		i++;
	}
}

void	check_walls_two(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	check_row_start(parsing, vars, directions);
	check_row_end(parsing, vars, directions);
}
