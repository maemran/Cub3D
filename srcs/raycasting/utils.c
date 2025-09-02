/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:16:15 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:49 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_cub3d *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(g->tex[i]);
		i++;
	}
}

void	free_structs(t_cub3d *g)
{
	if (g->color)
		free(g->color);
	if (g->dir)
		free(g->dir);
	if (g->data)
		free(g->data);
	if (g->rc)
		free(g->rc);
	if (g->tex)
		free(g->tex);
	free(g);
}

void	destroy_mlx(t_cub3d *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(g->data->mlx, g->tex[i]->img);
		i++;
	}
	mlx_destroy_image(g->data->mlx, g->data->img_buffer);
	mlx_destroy_window(g->data->mlx, g->data->win);
	mlx_destroy_display(g->data->mlx);
	free(g->data->mlx);
}

void	exit_window(t_cub3d *g)
{
	destroy_mlx(g);
	free_map(g);
	free_textures(g);
	free(g->dir->east);
	free(g->dir->north);
	free(g->dir->west);
	free(g->dir->south);
	free_structs(g);
	exit(0);
}

void	free_map(t_cub3d *g)
{
	int	i;

	i = 0;
	while (g->data->map[i])
	{
		free(g->data->map[i]);
		i++;
	}
	free(g->data->map);
}
