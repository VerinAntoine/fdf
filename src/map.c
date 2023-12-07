/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:45:13 by averin            #+#    #+#             */
/*   Updated: 2023/12/06 10:50:02 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// t_vector2	*iso_projection(t_vector3 *vector)
// {
// 	t_vector2	*result;

// 	result = ft_calloc(1, sizeof(t_vector2));
// 	if (!result)
// 		return (NULL);
// 	result->x = (vector->x - vector->z) * cos(0) * 40;
// 	result->y = ((vector->x + vector->z) * sin(50) - vector->y) * 10;
// 	return (result);
// }

t_vector3	*get_point(t_map *map, int x, int y)
{
	if (x < 0 || x > map->heigth || y < 0 || y > map->width)
		return (NULL);
	return (&(map->points[map->width * x + y]));
}

void	free_map(t_map *map)
{
	if (map->points)
		free(map->points);
	free(map);
}

void	print_map(t_map *map)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->heigth)
	{
		y = -1;
		while (++y < map->width)
			ft_printf("%d ", get_point(map, x, y)->z);
		ft_printf("\n");
	}
}
