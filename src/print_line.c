/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:30 by averin            #+#    #+#             */
/*   Updated: 2023/12/07 15:13:53 by averin           ###   ########.fr       */
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

void	print_line(t_point p0, t_point p1, t_data data)
{
	// TODO: norming
	int x0 = p0.x;
	int z0 = p0.z;
	int x1 = p1.x;
	int z1 = p1.z;
	int	dx = ft_abs(x0 - x1);
	int	dy = ft_abs(z0 - z1);
	int	sx = -ft_sign(x0 - x1);
	int	sy = -ft_sign(z0 - z1);
	printf("Drawing line from %d %d to %d %d\n", x0, z0, x1, z1);
	if (dy == 0)
	{
		while (x0 != x1 + sx)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, 0xFFFFFF);
			x0 += sx;
		}
	}
	else if (dx == 0)
	{
		while (z0 != z1 + sy)
		{
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, 0xFFFFFF);
			z0 += sy;
		}
	}
	else if (dx >= dy)
	{
		int slope = 2 * dy;
		int error = -dx;
		
		while (x0 != x1 + sx)
		{
			x0 += sx;
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, 0xFFFFFF);
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

		while (z0 != z1 + sy)
		{
			z0 += sy;
			mlx_pixel_put(data.mlx_ptr, data.window_ptr, z0, x0, 0xFFFFFF);
			error += slope;
			if (error >= 0)
			{
				x0 += sx;
				error += -2 * dy;
			}
		}
	}
}
