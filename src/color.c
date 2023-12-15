/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:03:39 by averin            #+#    #+#             */
/*   Updated: 2023/12/15 16:13:50 by averin           ###   ########.fr       */
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
 * @param map The map
 * @param y0 The y coordonate of the first point
 * @param y1 The y coordonate of the second point
 * @param colors Array of two to store the colors
*/
void	get_colors(t_map map, int y0, int y1, int *colors)
{
	colors[0] = lerp_color((int [2]){0xffffff, 0xff0000}, map.min_height,
			map.max_height, y0);
	colors[1] = lerp_color((int [2]){0xffffff, 0xff0000}, map.min_height,
			map.max_height, y1);
}
