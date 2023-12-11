/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:30 by averin            #+#    #+#             */
/*   Updated: 2023/12/11 14:09:57 by averin           ###   ########.fr       */
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

int	lerp_color(int start, int end, float i)
{
	int	c0[3];
	int	c1[3];

	c0[0] = start & 0xff0000 >> 16;
	c0[1] = start & 0x00ff00 >> 8;
	c0[2] = start & 0x0000ff;
	c1[0] = end & 0xff0000 >> 16;
	c1[1] = end & 0x00ff00 >> 8;
	c1[2] = end & 0x0000ff;
	printf("from %x to %x at %f => %x\n", start, end, i, (int) ((c0[0] - c1[0]) * i + c1[0]) << 16 |
			(int) ((c0[1] - c1[1]) * i + c1[1]) << 8 |
			(int) ((c0[2] - c1[2]) * i + c1[2]));
	return ((int) ((c0[0] - c1[0]) * i + c1[0]) << 16 |
			(int) ((c0[1] - c1[1]) * i + c1[1]) << 8 |
			(int) ((c0[2] - c1[2]) * i + c1[2]));
}

int	lerp(int start, int end, float i)
{
	if (i > 1)
		i = 1 - i;
	return (1 - i) * start + i * end;
}

int	plop(int hmax, int hmin, int height)
{
	return lerp_color(0xff0000, 0x110000, lerp(hmin, hmax, (height - hmin) * 1.0f / (hmax - hmin)));
}

void	print_line(t_point p0, t_point p1, t_data data)
{
	// TODO: norming
	int x0 = p0.u;
	int z0 = p0.v;
	int x1 = p1.u;
	int z1 = p1.v;
	
	// printf("draw line from %f %f %f to %f %f %f\n", p0.x, p0.y, p0.z, p1.x, p1.y, p1.z);
	int	dx = ft_abs(x0 - x1);
	int	dy = ft_abs(z0 - z1);
	int	scolor = plop(10, 0, ft_min(p0.y, p1.y));
	int ecolor = plop(10, 0, ft_max(p0.y, p1.y));
	printf("scolor %x\tecolor %x\n", scolor, ecolor);
	int	sx = -ft_sign(x0 - x1);
	int	sy = -ft_sign(z0 - z1);
	if (dy == 0)
	{
		while (x0 != x1)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, x0 * 1.0f / x1));
			x0 += sx;
		}
	}
	else if (dx == 0)
	{
		while (z0 != z1)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, z0 * 1.0f / z1));
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
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, x0 * 1.0f / x0));
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
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, z0 * 1.0f / z1));
			error += slope;
			if (error >= 0)
			{
				x0 += sx;
				error += -2 * dy;
			}
		}
	}
}
