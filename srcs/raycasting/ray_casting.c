/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:45:56 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:42 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_intersections(t_cub3d *g)
{
	if (g->rc->ray_dx < 0)
	{
		g->rc->step_x = -1;
		g->rc->side_x = (g->data->xp_pos - g->rc->map_x) * g->rc->delta_x;
	}
	else
	{
		g->rc->step_x = 1;
		g->rc->side_x = (g->rc->map_x + 1 - g->data->xp_pos) * g->rc->delta_x;
	}
	if (g->rc->ray_dy < 0)
	{
		g->rc->step_y = -1;
		g->rc->side_y = (g->data->yp_pos - g->rc->map_y) * g->rc->delta_y;
	}
	else
	{
		g->rc->step_y = 1;
		g->rc->side_y = (g->rc->map_y + 1 - g->data->yp_pos) * g->rc->delta_y;
	}
}

void	set_rc_values(t_cub3d *g, double camera_x)
{
	g->rc->ray_dx = g->rc->x_facing_dir + g->rc->cx_plane * camera_x;
	g->rc->ray_dy = g->rc->y_facing_dir + g->rc->cy_plane * camera_x;
	g->rc->delta_x = fabs(1 / g->rc->ray_dx);
	g->rc->delta_y = fabs(1 / g->rc->ray_dy);
	g->rc->map_x = (int)g->data->xp_pos;
	g->rc->map_y = (int)g->data->yp_pos;
}

void	dda_algorithm(t_cub3d *g)
{
	int	hit;

	hit = 0;
	g->rc->side = 0;
	while (!hit)
	{
		if (g->rc->side_x < g->rc->side_y)
		{
			g->rc->side_x += g->rc->delta_x;
			g->rc->map_x += g->rc->step_x;
			g->rc->side = 0;
		}
		else
		{
			g->rc->side_y += g->rc->delta_y;
			g->rc->map_y += g->rc->step_y;
			g->rc->side = 1;
		}
		if (check_map_cell(g, g->rc->map_x, g->rc->map_y))
			hit = 1;
	}
}

void	find_distance(t_cub3d *g)
{
	if (g->rc->side == 0)
		g->rc->dist = (g->rc->map_x - g->data->xp_pos + (1 - g->rc->step_x) / 2)
			/ g->rc->ray_dx;
	else
		g->rc->dist = (g->rc->map_y - g->data->yp_pos + (1 - g->rc->step_y) / 2)
			/ g->rc->ray_dy;
	g->rc->line_height = (int)(HIGHT / g->rc->dist);
	g->rc->start = -g->rc->line_height / 2 + HIGHT / 2;
	g->rc->end = g->rc->line_height / 2 + HIGHT / 2;
	if (g->rc->start < 0)
		g->rc->start = 0;
	if (g->rc->end >= HIGHT)
		g->rc->end = HIGHT - 1;
}

void	cast_ray(t_cub3d *g, int screen_x)
{
	double	camera_x;

	camera_x = 2 * screen_x / (double)WIDTH - 1;
	set_rc_values(g, camera_x);
	first_intersections(g);
	dda_algorithm(g);
	find_distance(g);
	set_texture_index(g);
	texture_position(g);
	draw_ceiling(g, screen_x);
	draw_walls(g, screen_x);
	draw_floor(g, screen_x);
}
