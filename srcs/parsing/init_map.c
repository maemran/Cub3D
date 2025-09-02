/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:06:58 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:39 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vars	*allocate_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
	{
		write(2, "Error\nmalloc error\n", 20);
		return (NULL);
	}
	vars->map = NULL;
	vars->map_height = 0;
	return (vars);
}

static int	get_map_height(t_parsing *parsing, int save_line)
{
	int	line;

	line = save_line;
	while (parsing->file[line])
		line++;
	return (line - save_line);
}

static void	free_partial_map(t_vars *vars, int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		free(vars->map[k]);
		k++;
	}
	free(vars->map);
	free(vars);
}

static int	copy_map_lines(t_parsing *parsing, t_vars *vars, int save_line,
		int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (parsing->file[save_line][j]
			&& parsing->file[save_line][j] != '\n')
			j++;
		vars->map[i] = malloc(sizeof(char) * (j + 1));
		if (!vars->map[i])
		{
			write(2, "Error\nmalloc error\n", 20);
			free_partial_map(vars, i);
			return (0);
		}
		ft_strlcpy(vars->map[i], parsing->file[save_line], j + 1);
		save_line++;
		i++;
	}
	vars->map[height] = NULL;
	return (1);
}

t_vars	*init_map(t_parsing *parsing)
{
	int		line;
	int		save_line;
	int		height;
	t_vars	*vars;

	line = first_line(parsing);
	if (!line)
		return (NULL);
	save_line = line;
	vars = allocate_vars();
	if (!vars)
		return (NULL);
	height = get_map_height(parsing, save_line);
	vars->map_height = height;
	vars->map = malloc(sizeof(char *) * (height + 1));
	if (!vars->map)
	{
		write(2, "Error\nmalloc error\n", 20);
		free(vars);
		return (NULL);
	}
	if (!copy_map_lines(parsing, vars, save_line, height))
		return (NULL);
	return (vars);
}
