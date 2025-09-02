/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:39:10 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:01 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_first_last_ceil(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	if (parsing->first_ceil == -1 || parsing->last_ceil == -1)
	{
		write(2, "Error\non init ceil", 19);
		free_all_and_exit(parsing, vars, directions);
	}
}

static int	get_ceil_line(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parsing->file[i])
	{
		j = 0;
		while (parsing->file[i][j] && parsing->file[i][j] != '\n')
		{
			if (parsing->file[i][j] == 'C')
			{
				parsing->ceil_line = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	set_ceil(t_parsing *parsing, t_vars *vars, t_directions *directions)
{
	int	j;

	j = 0;
	if (!get_ceil_line(parsing))
	{
		write(2, "Error\nC Rule Does Not Found\n", 29);
		free_all_and_exit(parsing, vars, directions);
	}
	while (parsing->file[parsing->ceil_line][j]
		&& parsing->file[parsing->ceil_line][j] != '\n')
	{
		if (parsing->file[parsing->ceil_line][j] == 'C')
		{
			parsing->first_ceil = j;
			while (parsing->file[parsing->ceil_line][j] != '\n'
				&& parsing->file[parsing->ceil_line][j])
			{
				parsing->last_ceil = j;
				j++;
			}
			break ;
		}
		j++;
	}
	check_first_last_ceil(parsing, vars, directions);
}

static void	check_comma_pos(t_parsing *parsing, t_vars *vars,
		t_directions *directions, int i)
{
	if (!ft_isdigit(parsing->ceil[i + 1]) || !ft_isdigit(parsing->ceil[i - 1]))
	{
		write(2, "Error\nafter and before comma should be number in ceil line",
			59);
		free_all_and_exit(parsing, vars, directions);
	}
}

void	check_comma_in_ceil(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int	i;
	int	count_comma;

	i = 0;
	count_comma = 0;
	while (parsing->ceil[i])
	{
		if (!ft_isalnum(parsing->ceil[i]) && parsing->ceil[i] != ','
			&& parsing->ceil[i] != 'C')
		{
			write(2, "Error\ninvalid char in ceil line", 32);
			free_all_and_exit(parsing, vars, directions);
		}
		if (parsing->ceil[i] == ',')
		{
			check_comma_pos(parsing, vars, directions, i);
			count_comma++;
		}
		i++;
	}
	if (count_comma != 2)
	{
		write(2, "Error\nthe number of comma is wrong in ceil line", 48);
		free_all_and_exit(parsing, vars, directions);
	}
}
