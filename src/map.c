/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:45:13 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 15:45:23 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	*get_point(t_map *map, size_t x, size_t y)
{
	if (x < 0 || x > map->height || y < 0 || y > map->width)
		return (NULL);
	return (&(map->points[map->width * x + y]));
}

void	free_map(t_map *map)
{
	if (map->points)
		free(map->points);
	free(map);
}
