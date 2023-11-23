/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:30 by averin            #+#    #+#             */
/*   Updated: 2023/11/23 18:25:37 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static float	abs(float f)
{
	if (f >= 0)
		return (f);
	return (-f);
}

static int	sign(float a, float b)
{
	if (a < b)
		return (1);
	return (-1);
}

int	do_add(float *error, float *v0, float dv, float sv)
{
	*error += dv;
	*v0 += sv;
	return (1);
}

void	do_line(float x[2], float y[2], t_data *data)
{
	float	dx;
	float	dy;
	int		sx;
	int		sy;
	float	error;

	dx = abs(x[1] - x[0]);
	dy = -abs(y[1] - y[0]);
	sx = sign(x[0], x[1]);
	sy = sign(y[0], y[1]);
	error = dx + dy;
	while (x[0] != x[1] && y[0] != y[1])
	{
		mlx_pixel_put(data->mlx_ptr, data->window_ptr, x[0], y[0], 0xFFFFFF);
		if (2 * error >= dy && (x[0] == x[1] || !do_add(&error, &x[0], dy, sx)))
			break ;
		if (2 * error <= dx && (y[0] == y[1] || !do_add(&error, &y[0], dx, sy)))
			break ;
	}
}

void	print_line(t_line *line, t_data *data)
{
	float	x[2];
	float	y[2];

	x[0] = line->a->x;
	x[1] = line->b->x;
	y[0] = line->a->y;
	y[1] = line->b->y;
	do_line(x, y, data);
}
