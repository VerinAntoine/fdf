/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:45:13 by averin            #+#    #+#             */
/*   Updated: 2023/12/14 15:53:20 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	*get_point(t_map *map, size_t x, size_t y)
{
	if (x > map->height || y > map->width)
		return (NULL);
	return (&(map->points[map->width * x + y]));
}

void	free_map(t_map *map)
{
	if (map->points)
		free(map->points);
	free(map);
}

void	find_heights(t_map *map)
{
	size_t	x;
	size_t	y;
	t_vec3	*point;
	int		min;
	int		max;

	min = INT_MAX;
	max = INT_MIN;
	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			point = get_point(map, x, y);
			if (point->y < min)
				min = point->y;
			if (point->y > max)
				max = point->y;
		}
	}
	map->max_height = max;
	map->min_height = min;
}

void	calibrate_map(t_map *map)
{
	(void) map;
	translate(map, (t_vec3){((int)map->height / 2) * -1.0f, 0,
		((int)map->width / 2) * -1.0f});
	scale(map, (t_vec3){HEIGHT / map->height * 0.5f, 1,
		WIDTH / map->width * 0.5f});
}
