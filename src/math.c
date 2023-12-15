/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:28:36 by averin            #+#    #+#             */
/*   Updated: 2023/12/14 14:44:27 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	vector_by_matrix(t_vec3 *point, t_matrix matrix)
{
	int	saves[3];

	saves[0] = point->x;
	saves[1] = point->y;
	saves[2] = point->z;
	point->x = saves[0] * matrix.i.x + saves[1] * matrix.i.y
		+ saves[2] * matrix.i.z;
	point->y = saves[0] * matrix.j.x + saves[1] * matrix.j.y
		+ saves[2] * matrix.j.z;
	point->z = saves[0] * matrix.k.x + saves[1] * matrix.k.y
		+ saves[2] * matrix.k.z;
}

static t_matrix	get_matrix(char c, float rad)
{
	if (c == AXIS_X)
		return ((t_matrix){
			{1, 0, 0},
			{0, cos(rad), -sin(rad)},
			{0, sin(rad), cos(rad)}
		});
	else if (c == AXIS_Y)
		return ((t_matrix){
			{cos(rad), 0, sin(rad)},
			{0, 1, 0},
			{-sin(rad), 0, cos(rad)}
		});
	else if (c == AXIS_Z)
		return ((t_matrix){
			{cos(rad), -sin(rad), 0},
			{sin(rad), cos(rad), 0},
			{0, 0, 1}
		});
	return ((t_matrix){
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	});
}

void	translate(t_map *map, t_vec3 v)
{
	size_t	x;
	size_t	y;
	t_vec3	*point;

	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			point = get_point(map, x, y);
			point->x += v.x;
			point->y += v.y;
			point->z += v.z;
		}
	}
}

void	scale(t_map *map, t_vec3 v)
{
	size_t	x;
	size_t	y;
	t_vec3	*point;

	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			point = get_point(map, x, y);
			point->x *= v.x;
			point->y *= v.y;
			point->z *= v.z;
		}
	}
}

void	rotate(t_map *map, float deg, char axis)
{
	size_t	x;
	size_t	y;

	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
			vector_by_matrix(get_point(map, x, y),
				get_matrix(axis, deg * 3.14 / 180));
	}
}
