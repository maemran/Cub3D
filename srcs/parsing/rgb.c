/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:04:59 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:11 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_valid_numbers(t_parsing *parsing, t_vars *vars,
		t_directions *directions, t_colors *colors)
{
	if (!(colors->ceil[0] >= 0 && colors->ceil[0] <= 255)
		|| !(colors->ceil[1] >= 0 && colors->ceil[1] <= 255)
		|| !(colors->ceil[2] >= 0 && colors->ceil[2] <= 255))
	{
		write(2, "Error\ninvalid numbers in ceil line", 35);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	if (!(colors->floor[0] >= 0 && colors->floor[0] <= 255)
		|| !(colors->floor[1] >= 0 && colors->floor[1] <= 255)
		|| !(colors->floor[2] >= 0 && colors->floor[2] <= 255))
	{
		write(2, "Error\ninvalid numbers in floor line", 36);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
}

static void	get_floor_number(t_parsing *parsing, t_vars *vars,
		t_directions *directions, t_colors *colors)
{
	int		i;
	char	**string;
	char	*line;

	i = 0;
	line = init_floor_numbers(parsing, vars, directions);
	if (!line)
	{
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	string = ft_split(line, ',');
	if (!string)
	{
		free(line);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	colors->floor[0] = ft_atoi(string[0]);
	colors->floor[1] = ft_atoi(string[1]);
	colors->floor[2] = ft_atoi(string[2]);
	free_string(string, i);
	free(line);
}

t_colors	*get_ceil_number(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int			i;
	char		**string;
	char		*line;
	t_colors	*colors;

	i = 0;
	line = init_ceil_numbers(parsing, vars, directions);
	colors = malloc(sizeof(t_colors));
	if (!colors)
		free_all_and_exit_two(parsing, vars, directions, line);
	string = ft_split(line, ',');
	if (!string)
	{
		free(line);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	colors->ceil[0] = ft_atoi(string[0]);
	colors->ceil[1] = ft_atoi(string[1]);
	colors->ceil[2] = ft_atoi(string[2]);
	free_string(string, i);
	free(line);
	get_floor_number(parsing, vars, directions, colors);
	check_valid_numbers(parsing, vars, directions, colors);
	return (colors);
}
