/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:49:11 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:24:08 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

static char	**alloc_file_buffer(int len)
{
	char	**file;

	file = malloc(sizeof(char *) * (len + 1));
	if (!file)
	{
		write(2, "Error\nmalloc error\n", 20);
		return (NULL);
	}
	return (file);
}

static void	fill_file_lines(int fd, char **file)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		file[i] = line;
		i++;
		line = get_next_line(fd);
	}
	file[i] = NULL;
}

char	**read_file(char *file_name)
{
	int		len;
	int		fd;
	char	**file;

	len = count_lines(file_name);
	if (len <= 0)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file = alloc_file_buffer(len);
	if (!file)
		return (NULL);
	fill_file_lines(fd, file);
	close(fd);
	return (file);
}
