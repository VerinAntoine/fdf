/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:30 by averin            #+#    #+#             */
/*   Updated: 2023/12/07 11:18:24 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
# include <stdio.h>
# include <unistd.h>

static int	ft_abs(int i)
{
	if (i >= 0)
		return (i);
	return (-i);
}

static int	ft_sign(int i)
{
	if (i < 0)
		return (-1);
	else if (i > 0)
		return (1);
	return (0);
}

void	print_line(t_point p0, t_point p1, t_data data)
{
	// float	x[2];
	// float	y[2];

	// x[0] = p0.x;
	// x[1] = p1.x;
	// y[0] = p0.y;
	// y[1] = p1.y;
	// do_line(x, y, data);
	int	dx = ft_abs(p0.x - p1.x);
	int	dy = ft_abs(p0.y - p1.y);
	int	sx = -ft_sign(p0.x - p1.x);
	int	sy = -ft_sign(p0.y - p1.y);
	if (dy == 0)
	{
		while (p0.x != p1.x + sx)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, p0.x, p0.y, 0xFFFFFF);
			p0.x += sx;
		}
	}
	else if (dx == 0)
	{
		while (p0.y != p1.y + sy)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, p0.x, p0.y, 0xFFFFFF);
			p0.y += sy;
		}
	}
	else if (dx >= dy)
	{
		int slope = 2 * dy;
		int error = -dx;
		
		while (p0.x != p1.x + sx)
		{
			p0.x += sx;
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, p0.x, p0.y, 0xFFFFFF);
			error += slope;
			if (error >= 0)
			{
				p0.y += sy;
				error += -2 * dx;
			}
		}
	}
	else
	{
		int slope = 2 * dx;
		int error = -dy;

		while (p0.y != p1.y + sy)
		{
			p0.y += sy;
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, p0.x, p0.y, 0xFFFFFF);
			error += slope;
			if (error >= 0)
			{
				p0.x += sx;
				error += -2 * dy;
			}
		}
	}
}
