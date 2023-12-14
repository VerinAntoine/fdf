/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:00:56 by averin            #+#    #+#             */
/*   Updated: 2023/12/14 14:54:55 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vec2	project(t_vec3 point)
{
	return ((t_vec2){point.z + WIDTH / 2, point.x + HEIGHT / 2});
}

static void	draw_fdf(t_data data, t_img *img)
{
	size_t	x;
	size_t	y;
	t_vec3	*a;
	t_vec3	*b;
	t_vec3	*c;

	x = -1;
	while (++x < data.map->height)
	{
		y = -1;
		while (++y < data.map->width)
		{
			a = get_point(data.map, x, y);
			b = get_point(data.map, x - 1, y);
			c = get_point(data.map, x, y - 1);
			if (!a)
				continue;
			if (b)
				draw_line(project(*a), project(*b), (int [2]){0, 0}, img);
			if (c)
				draw_line(project(*a), project(*c), (int [2]){0, 0}, img);
		}
	}
}

static void	create_img(t_data data)
{
	t_img	img;

	img.addr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	if (!img.addr)
		return ;
	img.content = mlx_get_data_addr(img.addr, &img.bpp, &img.size_line, &img.endian);
	draw_fdf(data, &img);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img.addr, 0, 0);
	mlx_destroy_image(data.mlx_ptr, img.addr);
}

int main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_dprintf(2, "Usage: %s <file.fdf>\n", argv[0]), -1);
	data.map = parse_map(argv[1]);
	if (!data.map)
		return (-2);
	if (!create_window(&data))
		return (free_map(data.map), ft_dprintf(2, "Couldn't create window\n"), -3);
	calibrate_map(data.map);
	create_img(data);
	init_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (delete_window(data), free_map(data.map), 0);
}
