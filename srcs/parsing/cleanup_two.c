/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:36:34 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:15 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_parsing(t_parsing *parsing)
{
	if (parsing)
	{
		if (parsing->file)
			free_file(parsing->file);
		if (parsing->ceil)
			free(parsing->ceil);
		if (parsing->floor)
			free(parsing->floor);
		free(parsing);
	}
}

void	free_directions(t_directions *directions)
{
	if (directions)
	{
		if (directions->east)
			free(directions->east);
		if (directions->north)
			free(directions->north);
		if (directions->south)
			free(directions->south);
		if (directions->west)
			free(directions->west);
		free(directions);
	}
}

void	free_vars(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars)
	{
		if (vars->map)
		{
			while (vars->map[i])
			{
				free(vars->map[i]);
				i++;
			}
			free(vars->map);
		}
		free(vars);
	}
}

void	free_string(char **string, int i)
{
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
}
