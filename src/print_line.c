/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:30 by averin            #+#    #+#             */
/*   Updated: 2023/12/06 17:20:36 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static int	ft_fabs(int f)
{
	if (f >= 0)
		return (f);
	return (-f);
}

static int	sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

static int	do_add(int *error, int *v0, int dv, int sv)
{
	*error += dv;
	*v0 += sv;
	return (1);
}

static void	do_line(int x[2], int y[2], t_data *data)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;

	dx = ft_fabs(x[1] - x[0]);
	dy = -ft_fabs(y[1] - y[0]);
	sx = sign(x[0], x[1]);
	sy = sign(y[0], y[1]);
	error = dx + dy;
	// printf(" - calling %f %f %f %f\n", x[0], x[1], y[0], y[1]);
	while (x[0] != x[1] && y[0] != y[1])
	{
		mlx_pixel_put(data->mlx_ptr, data->window_ptr, x[0], y[0], 0xFFFFFF);
		// printf(" - Putting pixel at %f %f (%f %f)\n", x[0], y[0], x[1], y[1]);
		if (2 * error >= dy && (x[0] == x[1] || !do_add(&error, &x[0], dy, sx)))
			continue ;
		if (2 * error <= dx && (y[0] == y[1] || !do_add(&error, &y[0], dx, sy)))
			continue ;
	}
}

void	print_line(t_vector2 *one, t_vector2 *two, t_data *data)
{
	int	x[2];
	int	y[2];

	printf("Printing line\n");
	x[0] = one->y;
	x[1] = two->y;
	y[0] = one->x;
	y[1] = two->x;
	do_line(x, y, data);
}
