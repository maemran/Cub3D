/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:29:35 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 12:55:48 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	program_check(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Error\nwrong number of arguments\n", 33);
		exit(1);
	}
	if (!valid_extension(argv))
	{
		write(2, "Error\n the extension of the file is wrong", 42);
		exit(1);
	}
}

static t_colors	*check_and_init(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	t_colors	*colors;

	check_lines(parsing, vars, directions);
	check_walls(parsing, vars, directions);
	check_image_path(parsing, vars, directions);
	colors = get_ceil_number(parsing, vars, directions);
	if (!colors)
	{
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	free_parsing(parsing);
	return (colors);
}

static void	ray_casting_part(t_cub3d *g, t_colors *colors, t_vars *vars,
		t_directions *directions)
{
	g = prepare_before_ray_casting(g, colors, vars, directions);
	if (!g)
	{
		ft_putstr_fd("Error\nMemory allocation failure\n", 2);
		exit(1);
	}
	mlx_manage(g);
}

int	main(int argc, char **argv)
{
	t_parsing		*parsing;
	t_directions	*directions;
	t_vars			*vars;
	t_cub3d			*g;
	t_colors		*colors;

	program_check(argc, argv);
	g = NULL;
	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (1);
	directions = malloc(sizeof(t_directions));
	if (!directions)
	{
		free(parsing);
		return (1);
	}
	if (!init_parsing_directions(parsing, directions, argv[1]))
		return (1);
	vars = init_map(parsing);
	if (!vars)
		free_all_and_exit(parsing, vars, directions);
	colors = check_and_init(parsing, vars, directions);
	ray_casting_part(g, colors, vars, directions);
	return (0);
}
