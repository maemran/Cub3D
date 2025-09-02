/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:28:13 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:20 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_and_free(t_parsing *parsing, t_vars *vars,
		t_directions *directions, char *str)
{
	write(2, str, ft_strlen(str));
	free_all_and_exit(parsing, vars, directions);
}

void	free_file(char **file)
{
	int	i;

	i = 0;
	if (!file)
		return ;
	while (file[i])
		free(file[i++]);
	free(file);
}

void	free_all_and_exit(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	free_parsing(parsing);
	free_directions(directions);
	free_vars(vars);
	exit(1);
}

void	exit_and_error(t_parsing *parsing, t_directions *directions, char *str)
{
	free_parsing(parsing);
	free_directions(directions);
	write(2, str, ft_strlen(str));
	exit(1);
}

void	free_all_and_exit_two(t_parsing *parsing, t_vars *vars,
		t_directions *directions, char *line)
{
	free_parsing(parsing);
	free_directions(directions);
	free_vars(vars);
	if (line)
		free(line);
	exit(1);
}
