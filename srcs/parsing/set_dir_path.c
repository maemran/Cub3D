/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:50:31 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:55:19 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	extract_path_bounds(char *line, t_parsing *parsing,
		t_path_info *info)
{
	if (!check_before_dir(info->line_index, info->j, parsing))
		return (0);
	info->j += 2;
	while (line[info->j] == ' ' || line[info->j] == '\t')
		info->j++;
	if (line[info->j] != '.')
		return (0);
	if (line[info->j + 1] != '/' && line[info->j + 1] != '.')
		return (0);
	info->start = info->j;
	while (line[info->j] && line[info->j] != '\n' && line[info->j] != ' '
		&& line[info->j] != '\t')
		info->j++;
	info->end = info->j;
	if (!check_after_path(info->line_index, info->j, parsing))
		return (0);
	return (1);
}

static int	scan_line(char *line, char *str, t_parsing *parsing,
		t_path_info *info)
{
	info->j = 0;
	while (line[info->j])
	{
		if (line[info->j] == '1' && is_this_map(parsing, info->line_index))
			return (0);
		if (match_identifier(line, info->j, str))
			return (extract_path_bounds(line, parsing, info));
		info->j++;
	}
	return (-1);
}

static int	find_path(t_parsing *parsing, char *str, t_path_info *info)
{
	int	i;
	int	result;

	i = 0;
	while (parsing->file[i])
	{
		info->line_index = i;
		result = scan_line(parsing->file[i], str, parsing, info);
		if (result == 1)
			return (1);
		else if (result == 0)
			return (0);
		i++;
	}
	return (0);
}

static int	copy_path(char **destination, char *line, t_path_info *info)
{
	int	k;
	int	start;
	int	end;

	k = 0;
	start = info->start;
	end = info->end;
	*destination = malloc(end - start + 1);
	if (!*destination)
	{
		write(2, "Error\nmalloc error", 19);
		return (0);
	}
	while (start < end)
		(*destination)[k++] = line[start++];
	(*destination)[k] = '\0';
	return (1);
}

int	set_dir_path(t_parsing *parsing, char **destination, char *str)
{
	t_path_info	info;

	if (!find_path(parsing, str, &info))
		return (0);
	return (copy_path(destination, parsing->file[info.line_index], &info));
}
