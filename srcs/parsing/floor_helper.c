/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:39:49 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:33 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_first_last_floor(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	if (parsing->first_floor == -1 || parsing->last_floor == -1)
	{
		write(2, "Error\non init ceil", 19);
		free_all_and_exit(parsing, vars, directions);
	}
}

static int	get_floor_line(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	parsing->floor_line = 0;
	while (parsing->file[i])
	{
		j = 0;
		while (parsing->file[i][j] && parsing->file[i][j] != '\n')
		{
			if (parsing->file[i][j] == 'F')
			{
				parsing->floor_line = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	set_floor(t_parsing *parsing, t_vars *vars, t_directions *directions)
{
	int	j;

	j = 0;
	if (!get_floor_line(parsing))
	{
		write(2, "Error\nF Rule Does Not Found\n", 29);
		free_all_and_exit(parsing, vars, directions);
	}
	while (parsing->file[parsing->floor_line][j]
		&& parsing->file[parsing->floor_line][j] != '\n')
	{
		if (parsing->file[parsing->floor_line][j] == 'F')
		{
			parsing->first_floor = j;
			while (parsing->file[parsing->floor_line][j] != '\n'
				&& parsing->file[parsing->floor_line][j])
			{
				parsing->last_floor = j;
				j++;
			}
			break ;
		}
		j++;
	}
	check_first_last_floor(parsing, vars, directions);
}

static void	check_comma_pos_f(t_parsing *parsing, t_vars *vars,
		t_directions *directions, int i)
{
	if (!ft_isdigit(parsing->floor[i + 1]) || !ft_isdigit(parsing->floor[i
				- 1]))
	{
		write(2, "Error\nafter and before comma should be number in floor line",
			60);
		free_all_and_exit(parsing, vars, directions);
	}
}

void	check_comma_in_floor(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int	i;
	int	count_comma;

	i = 0;
	count_comma = 0;
	while (parsing->floor[i])
	{
		if (!ft_isalnum(parsing->floor[i]) && parsing->floor[i] != ','
			&& parsing->floor[i] != 'F')
		{
			write(2, "Error\ninvalid char on floor line", 33);
			free_all_and_exit(parsing, vars, directions);
		}
		if (parsing->floor[i] == ',')
		{
			check_comma_pos_f(parsing, vars, directions, i);
			count_comma++;
		}
		i++;
	}
	if (count_comma != 2)
	{
		write(2, "Error\nthe number of comma is wrong", 35);
		free_all_and_exit(parsing, vars, directions);
	}
}
