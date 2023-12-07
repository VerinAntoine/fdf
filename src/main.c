/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:41 by averin            #+#    #+#             */
/*   Updated: 2023/12/07 15:14:45 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <math.h>

double	rad(double deg)
{
	return (deg * 3.14 / 180);
}

t_point	vector_by_matrix(t_point point, t_matrix matrix)
{
	int	saves[3] = {point.x, point.y, point.z};
	point.x = saves[0] * matrix.i.x + saves[1] * matrix.i.y + saves[2] * matrix.i.z;
	point.y = saves[0] * matrix.j.x + saves[1] * matrix.j.y + saves[2] * matrix.j.z;
	point.z = saves[0] * matrix.k.x + saves[1] * matrix.k.y + saves[2] * matrix.k.z;
	return (point);
}

t_point	do_maths(t_point *point)
{

	double r = atan(sqrt(2));
	t_matrix z = {
		{cos(r), -sin(r), 0},
		{sin(r),  cos(r), 0},
		{0, 0, 1}
	};
	r = rad(45);
	t_matrix y = {
		{cos(r), 0, sin(r)},
		{0, 1, 0},
		{-sin(r), 0, cos(r)}
	};
	t_point	p;
	p.x = point->x;
	p.y = point->y;
	p.z = point->z;

	printf("maths %f %f %f => \t", point->x, point->y, point->z);
	p.x -= 1 * p.y;
	p = vector_by_matrix(p, y);
	p = vector_by_matrix(p, z);
	p.x *= 20;
	p.y *= 20;
	p.z *= 20;

	p.x += HEIGHT / 2 - 100;
	p.z += WIDTH / 2 - 100;
	printf(" %f %f %f\n", p.x, p.y, p.z);

	return (p);
}

void	draw_lines(t_map *map, t_data *data)
{
	int		x;
	int		y;
	t_point	point;
	t_point	*next;

	x = -1;
	while (++x < map->heigth)
	{
		y = -1;
		while (++y < map->width)
		{
			printf("call for %d %d\n", x, y);
			point = do_maths(get_point(map, x, y));

			next = get_point(map, x - 1, y);
			if (next)
				print_line(point, do_maths(next), *data);
			next = get_point(map, x, y - 1);
			if (next)
				print_line(point, do_maths(next), *data);
		}
	}
}

int	key_hook(int keycode, t_data *param)
{
	if (keycode == XK_Escape)
	{
		mlx_clear_window(param->mlx_ptr, param->window_ptr);
		mlx_loop_end(param->mlx_ptr);
	}
	else if (keycode == XK_l)
		draw_lines(param->map, param);
	return (0);
}

int	main(int argc, char *argv[])
{ 
	if (argc != 2)
		return (ft_printf("Usage: %s map.fdf\n", argv[0]), 0);
	t_map	*map = parse(argv[1]);
	printf("Loaded map of %d by %d (%d points)\n", map->heigth, map->width, map->heigth * map->width);
	print_map(map);
	t_data	data = {0};
	data.map = map;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.window_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello");
	if (!data.window_ptr)
		return (1);
	mlx_key_hook(data.window_ptr, &key_hook, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.window_ptr);
	free(data.mlx_ptr);
	return (0);
}
