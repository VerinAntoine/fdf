/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:41 by averin            #+#    #+#             */
/*   Updated: 2023/12/06 17:00:44 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

t_vector2	*iso_projection(t_vector3 *vector, t_view *view)
{
	t_vector2	*result;

	result = ft_calloc(1, sizeof(t_vector2));
	if (!result)
		return (NULL);
	result->x = (vector->x - vector->z) * cos(view->c) * view->x + HEIGHT / 2;
	result->y = ((vector->x + vector->z) * sin(view->s) - vector->y) * view->y + WIDTH / 2;
	return (result);
}

void	draw_line(t_vector2 *point, int x, int y, t_map *map, t_data *data)
{
	t_vector3 *p = get_point(map, x, y);
	if (!p)
		return ;
	t_vector2 *r = iso_projection(p, data->view);
	print_line(point, r, data);
	free(r);
}

void	draw_lines(t_map *map, t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->heigth)
	{
		y = -1;
		while (++y < map->width)
		{
			t_vector2 *point = iso_projection(get_point(map, x, y), data->view);
			draw_line(point, x + 1, y, map, data);
			draw_line(point, x, y + 1, map, data);
		}
	}
}

void	draw_points(t_map *map, t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->heigth)
	{
		y = -1;
		while (++y < map->width)
		{
			t_vector3 *point = get_point(map, x, y);
			t_vector2 *r = iso_projection(point, data->view);
			mlx_pixel_put(data->mlx_ptr, data->window_ptr, (r->y) , (r->x), 0xFFFFFF);
			free(r);
			// char *str = ft_itoa(point->z);
			// mlx_string_put(data->mlx_ptr, data->window_ptr, point->y * WIDTH / map->width, point->x * HEIGHT / map->heigth, 0xFFFFFF, str);
			// free(str);
		}
	}
}

int	key_hook(int keycode, t_data *param)
{
	switch (keycode)
	{
	case XK_q:
		param->view->x += 1;
		break;
	case XK_a:
		param->view->x -= 1;
		break;
	case XK_w:
		param->view->y += 1;
		break;
	case XK_s:
		param->view->y -= 1;
		break;
	case XK_r:
		param->view->c += 0.5f;
		break;
	case XK_f:
		param->view->c -= 0.5f;
		break;
	case XK_t:
		param->view->s += 0.5f;
		break;
	case XK_g:
		param->view->s -= 0.5f;
		break;
	default:
		break;
	}

	mlx_clear_window(param->mlx_ptr, param->window_ptr);
	draw_points(param->map, param);

	if (keycode == XK_Escape)
	{
		mlx_clear_window(param->mlx_ptr, param->window_ptr);
		mlx_loop_end(param->mlx_ptr);
	}
	else if (keycode == XK_l)
	{
		draw_lines(param->map, param);
		// print_line(iso_projection(get_point(param->map, 0, 0), param->view), iso_projection(get_point(param->map, 1, 0), param->view), param);
	}
		
	return (0);
}

// void	draw_point(int x, int y, int z, t_data *data, int color)
// {
// 	t_vector3 v = { x, y, z };
// 	t_vector2 *p = iso_projection(&v);
// 	printf("point %d %d %d goes %f %f\n", v.x, v.y, v.z, p->x, p->y);
// 	mlx_pixel_put(data->mlx_ptr, data->window_ptr, p->y + WIDTH / 2, p->x + HEIGHT / 2, color);
// 	free(p);
// }

int	main(int ac, char *av[])
{ 
	if (ac != 2)
		return (ft_printf("Usage: %s map.fdf\n", av[0]), 0);
	t_map *map = parse(av[1]);

	t_view view = {25, 25, 1, 1};

	t_data	data = {0};
	data.map = map;
	data.view = &view;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.window_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Hello");
	if (!data.window_ptr)
		return (1);
	draw_points(map, &data);

	// draw_point(0, 0, 0, &data, 0xFFFF00);
	// draw_point(0, 0, 1, &data, 0x00FFFF);

	mlx_key_hook(data.window_ptr, &key_hook, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.window_ptr);
	free(data.mlx_ptr);
	free_map(map);
	return (0);
}
