/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:20:17 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:41 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_directions(t_directions *directions)
{
	directions->east = NULL;
	directions->north = NULL;
	directions->south = NULL;
	directions->west = NULL;
}

static void	init_parsing(t_parsing *parsing)
{
	parsing->ceil = NULL;
	parsing->floor = NULL;
	parsing->file = NULL;
	parsing->ceil_line = -1;
	parsing->first_ceil = -1;
	parsing->first_floor = -1;
	parsing->floor_line = -1;
	parsing->last_ceil = -1;
	parsing->last_floor = -1;
}

int	init_parsing_directions(t_parsing *parsing, t_directions *directions,
		char *argv)
{
	init_parsing(parsing);
	parsing->file = read_file(argv);
	if (!parsing->file)
	{
		write(2, "Error\non opening the fd", 24);
		free(parsing);
		free(directions);
		return (0);
	}
	set_directions(parsing, directions);
	return (1);
}

void	check_image_path(t_parsing *parsing, t_vars *vars,
		t_directions *directinos)
{
	int	fd_ea;
	int	fd_no;
	int	fd_so;
	int	fd_we;

	fd_ea = open(directinos->east, O_RDONLY);
	if (fd_ea == -1)
		print_and_free(parsing, vars, directinos, "Error\nbad path\n");
	close(fd_ea);
	fd_no = open(directinos->north, O_RDONLY);
	if (fd_no == -1)
		print_and_free(parsing, vars, directinos, "Error\nbad path\n");
	close(fd_no);
	fd_so = open(directinos->south, O_RDONLY);
	if (fd_so == -1)
		print_and_free(parsing, vars, directinos, "Error\nbad path\n");
	close(fd_so);
	fd_we = open(directinos->west, O_RDONLY);
	if (fd_we == -1)
		print_and_free(parsing, vars, directinos, "Error\nbad path\n");
	close(fd_we);
}
