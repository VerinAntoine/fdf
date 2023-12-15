/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:00:56 by averin            #+#    #+#             */
/*   Updated: 2023/12/15 16:08:28 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_vec3	project(t_vec3 point)
{
	return ((t_vec3){point.z + WIDTH / 2, point.y, point.x + HEIGHT / 2});
}

static void	draw_lines(t_map *origin, t_map *map, size_t c[2], t_img *img)
{
	t_vec3	*points[3];
	int		colors[2];

	points[0] = get_point(map, c[0], c[1]);
	points[1] = get_point(map, c[0] - 1, c[1]);
	points[2] = get_point(map, c[0], c[1] - 1);
	if (!points[0])
		return ;
	if (points[1])
	{
		get_colors(*origin, get_point(origin, c[0], c[1])->y,
			get_point(origin, c[0] - 1, c[1])->y, colors);
		draw_line(project(*points[0]), project(*points[1]), colors, img);
	}
	if (points[2])
	{
		get_colors(*origin, get_point(origin, c[0], c[1])->y,
			get_point(origin, c[0], c[1] - 1)->y, colors);
		draw_line(project(*points[0]), project(*points[2]), colors, img);
	}
}

void	draw_fdf(t_data data, t_img *img)
{
	size_t	x;
	size_t	y;
	t_map	*map;

	map = duplicate_map(data.map);
	scale(map, (t_vec3){data.view->scale, data.view->height
		* data.view->scale, data.view->scale});
	rotate(map, data.view->deg_x, AXIS_X);
	rotate(map, data.view->deg_y, AXIS_Y);
	rotate(map, data.view->deg_z, AXIS_Z);
	x = -1;
	while (++x < map->height)
	{
		y = -1;
		while (++y < map->width)
			draw_lines(data.map, map, (size_t [2]){x, y}, img);
	}
	free_map(map);
}

static void	init_view(t_view *view, int size)
{
	view->deg_x = 0;
	view->deg_y = 0;
	view->deg_z = 0;
	view->scale = ft_max(HEIGHT, WIDTH) / size * 0.5f;
	view->height = 1;
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_view	view;

	if (argc != 2)
		return (ft_dprintf(2, "Usage: %s <file.fdf>\n", argv[0]), -1);
	data.map = parse_map(argv[1]);
	if (!data.map)
		return (-2);
	init_view(&view, ft_max(data.map->width, data.map->height));
	data.view = &view;
	if (!create_window(&data))
		return (free_map(data.map), ft_dprintf(2, "Couldn't create window\n"), \
		-3);
	calibrate_map(data.map);
	create_img(data);
	init_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (delete_window(data), free_map(data.map), 0);
}
