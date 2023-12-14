/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:03:39 by averin            #+#    #+#             */
/*   Updated: 2023/12/14 17:24:04 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	lerp_color(int *colors, int start, int end, int current)
{
	int		r;
	int		g;
	int		b;
	float	i;

	i = (current - start) * 1.0f / (end - start);
	r = (colors[0] & 0xff0000) * (1 - i) + (colors[1] & 0xff0000) * i;
	g = (colors[0] & 0x00ff00) * (1 - i) + (colors[1] & 0x00ff00) * i;
	b = (colors[0] & 0x0000ff) * (1 - i) + (colors[1] & 0x0000ff) * i;
	// printf("from %x to %x with %f\n", colors[0], colors[1], i);
	return ((r & 0xff0000) | (g & 0x00ff00) | (b & 0x0000ff));
}

int	*get_colors(t_map map, int y0, int y1)
{
	return ((int [2]){
		lerp_color((int [2]){0xffffff, 0xff0000}, map.min_height,
		map.max_height, y0),
		lerp_color((int [2]){0xffffff, 0xff0000}, map.min_height,
		map.max_height, y1)
	});
}
