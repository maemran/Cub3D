/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_res.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:49:20 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:18 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_resources_before_map(t_parsing *parsing)
{
	int	i;
	int	j;
	int	not_empty;

	i = 0;
	not_empty = 0;
	while (parsing->file[i])
	{
		j = 0;
		while (parsing->file[i][j] && parsing->file[i][j] != '\n')
		{
			if (parsing->file[i][j] == '1' && is_this_map(parsing, i))
				return (not_empty);
			if (ft_isalnum(parsing->file[i][j]))
			{
				not_empty++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (not_empty);
}

static void	validate_resource_count(int count, t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	if (count != 6)
	{
		write(2, "Error\nthe numbers of resources is wrong", 40);
		free_all_and_exit(parsing, vars, directions);
	}
}

void	check_lines(t_parsing *parsing, t_vars *vars, t_directions *directions)
{
	int	not_empty;

	not_empty = count_resources_before_map(parsing);
	validate_resource_count(not_empty, parsing, vars, directions);
	init_ceil(parsing, vars, directions);
	check_comma_in_ceil(parsing, vars, directions);
}
