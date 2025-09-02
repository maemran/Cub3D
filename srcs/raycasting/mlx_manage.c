/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:35:42 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:51:46 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rendering(t_cub3d *g)
{
	int	x;

	x = 0;
	smooth_keys(g);
	while (x < WIDTH)
	{
		cast_ray(g, x);
		x++;
	}
	mlx_put_image_to_window(g->data->mlx, g->data->win, g->data->img_buffer, 0,
		0);
	return (0);
}

static int	close_button(t_cub3d *g)
{
	exit_window(g);
	return (0);
}

static int	mouse_move(int x, int y, t_cub3d *g)
{
	static int	last_x = WIDTH / 2;
	int			delta_x;

	(void)y;
	delta_x = x - last_x;
	if (delta_x > 0)
		rotate_player(g, ROTATSPEED * 1.4);
	else if (delta_x < 0)
		rotate_player(g, -ROTATSPEED * 1.4);
	last_x = x;
	return (0);
}

void	mlx_manage(t_cub3d *g)
{
	g->data->mlx = mlx_init();
	g->data->win = mlx_new_window(g->data->mlx, WIDTH, HIGHT, "CUB3D");
	g->data->img_buffer = mlx_new_image(g->data->mlx, WIDTH, HIGHT);
	g->data->img_addr = mlx_get_data_addr(g->data->img_buffer, &g->data->bpp,
			&g->data->line_length, &g->data->endian);
	set_directions_values(g);
	load_texture(g, 0, g->dir->north);
	load_texture(g, 1, g->dir->south);
	load_texture(g, 2, g->dir->east);
	load_texture(g, 3, g->dir->west);
	get_ceiling_color(g);
	get_floor_color(g);
	keys_init(g);
	mlx_hook(g->data->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->data->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->data->win, 17, 0, close_button, g);
	mlx_hook(g->data->win, 6, 1L << 6, mouse_move, g);
	mlx_loop_hook(g->data->mlx, rendering, g);
	mlx_loop(g->data->mlx);
}
