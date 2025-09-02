/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:56:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:06 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_extension(char **argv)
{
	char	*name;
	int		len;

	name = argv[1];
	len = (int)ft_strlen(name);
	if (name[len - 1] == 'b' && name[len - 2] == 'u' && name[len - 3] == 'c'
		&& name[len - 4] == '.' && ft_isalnum(name[len - 5]))
		return (1);
	return (0);
}

static int	is_map_line(t_parsing *parsing, int i)
{
	int	j;

	j = 0;
	while (parsing->file[i][j] && parsing->file[i][j] != '\n')
	{
		if (parsing->file[i][j] == '1' && is_this_map(parsing, i))
			return (1);
		j++;
	}
	return (0);
}

int	first_line(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->file[i])
	{
		if (is_map_line(parsing, i))
			return (i);
		i++;
	}
	write(2, "Error\nthere is no map", 22);
	return (0);
}
