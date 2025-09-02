/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:15:35 by maemran           #+#    #+#             */
/*   Updated: 2025/08/26 11:16:31 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *g)
{
	move_player(g, g->rc->x_facing_dir * MOVESPEED, g->rc->y_facing_dir
		* MOVESPEED);
}

void	move_backward(t_cub3d *g)
{
	move_player(g, -g->rc->x_facing_dir * MOVESPEED, -g->rc->y_facing_dir
		* MOVESPEED);
}

void	move_left(t_cub3d *g)
{
	move_player(g, g->rc->y_facing_dir * MOVESPEED, -g->rc->x_facing_dir
		* MOVESPEED);
}

void	move_right(t_cub3d *g)
{
	move_player(g, -g->rc->y_facing_dir * MOVESPEED, g->rc->x_facing_dir
		* MOVESPEED);
}

void	rotate_left(t_cub3d *g)
{
	rotate_player(g, -ROTATSPEED);
}
