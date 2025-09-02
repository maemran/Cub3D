/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:10:41 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:23:23 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_after_path(int i, int check, t_parsing *parsing)
{
	while (parsing->file[i][check] != '\n' && parsing->file[i][check])
	{
		if ((parsing->file[i][check] != ' ' && parsing->file[i][check] != '\t'))
			return (0);
		check++;
	}
	return (1);
}

int	check_before_dir(int i, int j, t_parsing *parsing)
{
	if (j == 0)
		return (1);
	j--;
	while (j >= 0)
	{
		if (parsing->file[i][j] != ' ' && parsing->file[i][j] != '\t')
			return (0);
		j--;
	}
	return (1);
}

int	match_identifier(char *line, int j, char *str)
{
	return (line[j] == str[0] && line[j + 1] == str[1]);
}
