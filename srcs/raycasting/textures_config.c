/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:38:14 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:46 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_cub3d *g, int x, int y, int color)
{
	*(int *)(g->data->img_addr + y * g->data->line_length + x * (g->data->bpp
				/ 8)) = color;
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	pixel;

	if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
		return (0);
	pixel = *(int *)(tex->addr + y * tex->line_len + x * (tex->bpp / 8));
	return (pixel);
}

void	set_texture_index(t_cub3d *g)
{
	g->rc->tex_id = 0;
	if (g->rc->side == 0)
	{
		if (g->rc->ray_dx < 0)
			g->rc->tex_id = 3;
		else
			g->rc->tex_id = 2;
	}
	else
	{
		if (g->rc->ray_dy < 0)
			g->rc->tex_id = 0;
		else
			g->rc->tex_id = 1;
	}
}

void	texture_position(t_cub3d *g)
{
	double	wall_x;

	if (g->rc->side == 0)
		wall_x = g->data->yp_pos + g->rc->dist * g->rc->ray_dy;
	else
		wall_x = g->data->xp_pos + g->rc->dist * g->rc->ray_dx;
	wall_x -= floor(wall_x);
	g->rc->tex_x = (int)(wall_x * TEX_SIZE);
	if ((g->rc->side == 0 && g->rc->ray_dx > 0) || (g->rc->side == 1
			&& g->rc->ray_dy < 0))
		g->rc->tex_x = TEX_SIZE - g->rc->tex_x - 1;
	g->rc->step = 1.0 * TEX_SIZE / g->rc->line_height;
	g->rc->tex_pos = (g->rc->start - HIGHT / 2 + g->rc->line_height / 2)
		* g->rc->step;
}

void	load_texture(t_cub3d *g, int index, char *path)
{
	g->tex[index]->img = mlx_xpm_file_to_image(g->data->mlx, path,
			&g->tex[index]->line_len, &g->tex[index]->endian);
	g->tex[index]->addr = mlx_get_data_addr(g->tex[index]->img,
			&g->tex[index]->bpp, &g->tex[index]->line_len,
			&g->tex[index]->endian);
}
