/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:55:59 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 12:46:42 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_directions_values(t_cub3d *g)
{
	double	angle;

	angle = 0.0;
	if (g->data->facing_dir == 'E')
		angle = 0;
	else if (g->data->facing_dir == 'N')
		angle = M_PI / 2;
	else if (g->data->facing_dir == 'W')
		angle = M_PI;
	else if (g->data->facing_dir == 'S')
		angle = (3 * M_PI) / 2;
	g->rc->x_facing_dir = cos(angle);
	g->rc->y_facing_dir = -sin(angle);
	g->rc->cx_plane = -g->rc->y_facing_dir * FOV_FACTOR;
	g->rc->cy_plane = g->rc->x_facing_dir * FOV_FACTOR;
}

int	check_map_cell(t_cub3d *g, int x, int y)
{
	if (x < 0 || x >= g->data->map_width || y < 0 || y >= g->data->map_height)
		return (1);
	if (g->data->map[y][x] == '1')
		return (1);
	return (0);
}

void	rotate_player(t_cub3d *g, double angle)
{
	double	old_dx;
	double	old_cx;

	old_dx = g->rc->x_facing_dir;
	old_cx = g->rc->cx_plane;
	g->rc->x_facing_dir = g->rc->x_facing_dir * cos(angle) - g->rc->y_facing_dir
		* sin(angle);
	g->rc->y_facing_dir = old_dx * sin(angle) + g->rc->y_facing_dir
		* cos(angle);
	g->rc->cx_plane = g->rc->cx_plane * cos(angle) - g->rc->cy_plane
		* sin(angle);
	g->rc->cy_plane = old_cx * sin(angle) + g->rc->cy_plane * cos(angle);
}

void	move_player(t_cub3d *g, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = g->data->xp_pos + move_x;
	new_y = g->data->yp_pos + move_y;
	if (!check_map_cell(g, (int)new_x, (int)g->data->yp_pos))
		g->data->xp_pos = new_x;
	if (!check_map_cell(g, (int)g->data->xp_pos, (int)new_y))
		g->data->yp_pos = new_y;
}
