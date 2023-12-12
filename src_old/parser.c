/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:02:16 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 09:02:05 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfo.h"

static t_map	*get_map_info(int fd, t_map *map)
{
	char	*line;
	size_t	width;
	size_t	height;

	if (!oget_next_line(fd, &line))
		return (NULL);
	height = 1;
	width = ft_count_words(line, ' ');
	free(line);
	while (oget_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	map->heigth = height;
	map->width = width;
	return (map);
}

static int	parse_line(char *line, t_map *map, int x)
{
	char	**elements;
	t_point	*point;
	int		y;

	y = -1;
	elements = ft_split(line, ' ');
	if (!elements)
		return (FALSE);
	while (elements[++y])
	{
		point = get_point(map, x, y);
		point->x = x;
		point->y = ft_atoi(elements[y]);
		point->z = y;
	}
	ft_free_split(elements);
	return (TRUE);
}

static int	init_map(int fd, t_map *map)
{
	char	*line;
	size_t	x;

	x = 0;
	map->points = ft_calloc(map->heigth * map->width, sizeof(t_point));
	if (!map->points)
		return (ft_dprintf(2, "Memory error\n"), FALSE);
	while (oget_next_line(fd, &line))
	{
		if (!parse_line(line, map, x++))
			return (ft_dprintf(2, "Memory error\n"), FALSE);
		free(line);
	}
	return (TRUE);
}

t_map	*parse(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(2, "Invalid file name\n"), NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (ft_dprintf(2, "Memory error\n"), NULL);
	get_map_info(fd, map);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free_map(map), ft_dprintf(2, "Invalid file name\n"), NULL);
	if (!init_map(fd, map))
		return (free_map(map), NULL);
	close(fd);
	return (map);
}
