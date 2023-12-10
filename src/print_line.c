/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:30 by averin            #+#    #+#             */
/*   Updated: 2023/12/10 14:09:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
# include <stdio.h>
# include <unistd.h>

static int	ft_sign(int i)
{
	if (i < 0)
		return (-1);
	else if (i > 0)
		return (1);
	return (0);
}

int	lerp(int start, int end, float i)
{
	printf("lerp: from %d to %d at %f = %f\n", start, end, i, (1 - i) * start + i * end);
	return i * start + i * end;
}

int	plop(int hmax, int hmin, int height)
{
	// hmax => 0xffffff => 1
	// hmin => 0xfa5fe2 => 0
	return lerp(0xffffff, 0xfa5fe2, lerp(hmin, hmax, (height - hmin) / (hmax - hmin)));
}

void	print_line(t_point p0, t_point p1, t_data data)
{
	// TODO: norming
	int x0 = p0.x;
	int z0 = p0.z;
	int x1 = p1.x;
	int z1 = p1.z;
	
	int	dx = ft_abs(x0 - x1);
	int	dy = ft_abs(z0 - z1);
	int	scolor = plop(10, 0, p0.y);
	int ecolor = plop(10, 0, p1.y);
	int	sx = -ft_sign(x0 - x1);
	int	sy = -ft_sign(z0 - z1);
	if (dy == 0)
	{
		while (x0 != x1)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp(scolor, ecolor, x0 * 1.0f / x1));
			x0 += sx;
		}
	}
	else if (dx == 0)
	{
		while (z0 != z1)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp(scolor, ecolor, z0 * 1.0f / z1));
			z0 += sy;
		}
	}
	else if (dx >= dy)
	{
		int slope = 2 * dy;
		int error = -dx;
		
		while (x0 != x1)
		{
			x0 += sx;
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp(scolor, ecolor, x1 * 1.0f / x0));
			error += slope;
			if (error >= 0)
			{
				z0 += sy;
				error += -2 * dx;
			}
		}
	}
	else
	{
		int slope = 2 * dx;
		int error = -dy;

		while (z0 != z1)
		{
			z0 += sy;
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp(scolor, ecolor, z0 * 1.0f / z1));
			error += slope;
			if (error >= 0)
			{
				x0 += sx;
				error += -2 * dy;
			}
		}
	}
}
