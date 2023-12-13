/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:30 by averin            #+#    #+#             */
/*   Updated: 2023/12/13 12:43:13 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfo.h"
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
	int r = (start & 0xff0000) * (1 - i) + (end & 0xff0000) * i;
	int g = (start & 0x00ff00) * (1 - i) + (end & 0x00ff00) * i;
	int b = (start & 0x0000ff) * (1 - i) + (end & 0x0000ff) * i;
	return ((r & 0xff0000) | (g & 0x00ff00) | (b & 0x0000ff));
}

int	lerp(int start, int end, float i)
{
	return (1 - i) * start + i * end;
}

int	plop(int hmax, int hmin, int height)
{
	return lerp_color(0xffffff, 0xff0000, (height - hmin) * 1.0f / (hmax - hmin));
}

float	ft_div(int start, float a, float b)
{
	return ((a - start) * 1.0f / (b - start));
}

void	print_line(t_point p0, t_point p1, t_data data)
{
	// TODO: norming
	int x0 = p0.u;
	int z0 = p0.v;
	int x1 = p1.u;
	int z1 = p1.v;
	
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
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, ft_div(p0.u, x0, x1)));
			x0 += sx;
		}
	}
	else if (dx == 0)
	{
		while (z0 != z1)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, ft_div(p0.v, z0, z1)));
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
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, ft_div(p0.u, x0, x1)));
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
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, lerp_color(scolor, ecolor, ft_div(p0.v, z0, z1)));
			error += slope;
			if (error >= 0)
			{
				x0 += sx;
				error += -2 * dy;
			}
		}
	}
}
