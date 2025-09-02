/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:03:57 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:01 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_first_non_whitespace(char *line)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] != ' ' && line[j] != '\t')
			return (j);
		j++;
	}
	return (-1);
}

static int	get_last_non_whitespace(char *line)
{
	int	j;
	int	last;

	j = 0;
	last = -1;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] != ' ' && line[j] != '\t')
			last = j;
		j++;
	}
	return (last);
}

static int	check_tabs_in_bounds(char *line, int start, int end)
{
	int	j;

	j = start;
	while (j <= end)
	{
		if (line[j] == '\t')
			return (0);
		j++;
	}
	return (1);
}

static void	validate_map_line(int i, t_vars *vars, t_parsing *parsing,
		t_directions *dirs)
{
	char	*line;
	int		first;
	int		last;

	line = vars->map[i];
	first = get_first_non_whitespace(line);
	last = get_last_non_whitespace(line);
	if (first == -1)
		print_and_free(parsing, vars, dirs, "Error\nEmpty line inside map\n");
	if (!check_tabs_in_bounds(line, first, last))
		print_and_free(parsing, vars, dirs, "Error\nfound tab inside the map");
}

void	check_taps(t_parsing *parsing, t_vars *vars, t_directions *dirs)
{
	int	last_line;
	int	i;

	i = 0;
	last_line = get_last_line(vars, parsing);
	while (i < last_line)
	{
		validate_map_line(i, vars, parsing, dirs);
		i++;
	}
	check_elements(parsing, vars, dirs);
	restore_map(vars);
}
