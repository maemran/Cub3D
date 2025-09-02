/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:23:40 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:04 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_space_after_number(t_parsing *parsing, t_vars *vars,
		t_directions *directions, int j)
{
	int	k;

	k = j + 1;
	while (parsing->file[parsing->ceil_line][k] == ' ')
		k++;
	if (ft_isdigit(parsing->file[parsing->ceil_line][k]))
		print_and_free(parsing, vars, directions,
			"Error\nspace inside the number field");
}

void	check_space_in_ceil(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		j;
	int		in_number;
	char	c;

	j = 0;
	in_number = 0;
	while (parsing->file[parsing->ceil_line][j]
		&& parsing->file[parsing->ceil_line][j] != '\n')
	{
		c = parsing->file[parsing->ceil_line][j];
		if (ft_isdigit(c))
			in_number = 1;
		else if (c == ' ' || c == '\t')
		{
			if (in_number)
			{
				check_space_after_number(parsing, vars, directions, j);
				in_number = 0;
			}
		}
		else if (c == ',')
			in_number = 0;
		j++;
	}
}

static void	check_space_after_number_f(t_parsing *parsing, t_vars *vars,
		t_directions *directions, int j)
{
	int	k;

	k = j + 1;
	while (parsing->file[parsing->floor_line][k] == ' ')
		k++;
	if (ft_isdigit(parsing->file[parsing->floor_line][k]))
		print_and_free(parsing, vars, directions,
			"Error\nspace inside the number field");
}

void	check_space_in_floor(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		j;
	int		in_number;
	char	c;

	j = 0;
	in_number = 0;
	while (parsing->file[parsing->floor_line][j]
		&& parsing->file[parsing->floor_line][j] != '\n')
	{
		c = parsing->file[parsing->floor_line][j];
		if (ft_isdigit(c))
			in_number = 1;
		else if (c == ' ' || c == '\t')
		{
			if (in_number)
			{
				check_space_after_number_f(parsing, vars, directions, j);
				in_number = 0;
			}
		}
		else if (c == ',')
			in_number = 0;
		j++;
	}
}
