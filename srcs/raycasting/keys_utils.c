/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:20:15 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 12:57:50 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_cub3d *g)
{
	if (key == XK_Escape)
		g->keys.escape = 1;
	if (key == XK_w)
		g->keys.w = 1;
	if (key == XK_s)
		g->keys.s = 1;
	if (key == XK_a)
		g->keys.a = 1;
	if (key == XK_d)
		g->keys.d = 1;
	if (key == XK_Left)
		g->keys.left = 1;
	if (key == XK_Right)
		g->keys.right = 1;
	return (0);
}

int	key_release(int key, t_cub3d *g)
{
	if (key == XK_Escape)
		g->keys.escape = 0;
	if (key == XK_w)
		g->keys.w = 0;
	if (key == XK_s)
		g->keys.s = 0;
	if (key == XK_a)
		g->keys.a = 0;
	if (key == XK_d)
		g->keys.d = 0;
	if (key == XK_Left)
		g->keys.left = 0;
	if (key == XK_Right)
		g->keys.right = 0;
	return (0);
}

void	smooth_keys(t_cub3d *g)
{
	if (g->keys.escape)
		handle_escape(g);
	if (g->keys.w)
		move_forward(g);
	if (g->keys.s)
		move_backward(g);
	if (g->keys.a)
		move_left(g);
	if (g->keys.d)
		move_right(g);
	if (g->keys.left)
		rotate_left(g);
	if (g->keys.right)
		rotate_right(g);
}

void	rotate_right(t_cub3d *g)
{
	rotate_player(g, ROTATSPEED);
}

void	handle_escape(t_cub3d *g)
{
	exit_window(g);
}
