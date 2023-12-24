/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:03:39 by averin            #+#    #+#             */
/*   Updated: 2023/12/24 15:20:02 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Linear interpolation of two colors
 * @param colors Array of the two colors to interpolate
 * @param start The start point of the interpolation
 * @param end The end point of the interpolation
 * @param current The current point of the interpolation
*/
int	lerp_color(int *colors, int start, int end, int current)
{
	int		r;
	int		g;
	int		b;
	float	i;

	if (start == end)
		return (colors[0]);
	i = (current - start) * 1.0f / (end - start);
	r = (colors[0] & 0xff0000) * (1 - i) + (colors[1] & 0xff0000) * i;
	g = (colors[0] & 0x00ff00) * (1 - i) + (colors[1] & 0x00ff00) * i;
	b = (colors[0] & 0x0000ff) * (1 - i) + (colors[1] & 0x0000ff) * i;
	return ((r & 0xff0000) | (g & 0x00ff00) | (b & 0x0000ff));
}

/**
 * Get the gradient for the line between two points
 * @param data Execution data
 * @param y0 The y coordonate of the first point
 * @param y1 The y coordonate of the second point
 * @param colors Array of two to store the colors
*/
void	get_colors(t_data data, int y0, int y1, int *colors)
{
	colors[0] = lerp_color((int [2]){data.color->start, data.color->end},
			data.map->min_height, data.map->max_height, y0);
	colors[1] = lerp_color((int [2]){data.color->start, data.color->end},
			data.map->min_height, data.map->max_height, y1);
}

t_color	*change_color(t_color *color, int id)
{
	if (id == 0)
	{
		color->start = 0xffffff;
		color->end = 0x00ff00;
	}
	else if (id == 1)
	{
		color->start = 0xffffff;
		color->end = 0xff0000;
	}
	else if (id == 2)
	{
		color->start = 0xffffff;
		color->end = 0x0000ff;
	}
	else if (id == 3)
	{
		color->start = 0xffffff;
		color->end = 0xffffff;
	}
	return (color);
}
