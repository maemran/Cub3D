/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:48:49 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:22 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_cub3d *g, int screen_x)
{
	g->rc->i = 0;
	while (g->rc->i < g->rc->start)
	{
		put_pixel(g, screen_x, g->rc->i, g->color->c_mix);
		g->rc->i++;
	}
}

void	draw_walls(t_cub3d *g, int screen_x)
{
	int	color;

	while (g->rc->i < g->rc->end)
	{
		g->rc->tex_y = (int)(g->rc->tex_pos) & (TEX_SIZE - 1);
		g->rc->tex_pos += g->rc->step;
		color = get_texture_pixel(g->tex[g->rc->tex_id], g->rc->tex_x,
				g->rc->tex_y);
		put_pixel(g, screen_x, g->rc->i, color);
		g->rc->i++;
	}
}

void	draw_floor(t_cub3d *g, int screen_x)
{
	while (g->rc->i < HIGHT)
	{
		put_pixel(g, screen_x, g->rc->i, g->color->f_mix);
		g->rc->i++;
	}
}

void	get_ceiling_color(t_cub3d *g)
{
	g->color->c_mix = (g->color->ceil[0] << 16) | (g->color->ceil[1] << 8)
		| g->color->ceil[2];
}

void	get_floor_color(t_cub3d *g)
{
	g->color->f_mix = (g->color->floor[0] << 16)
		| (g->color->floor[1] << 8) | g->color->floor[2];
}
