/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:00:56 by averin            #+#    #+#             */
/*   Updated: 2023/12/13 13:48:34 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	create_img(t_data data)
{
	t_img	img;

	img.addr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	if (!img.addr)
		return ;
	img.content = mlx_get_data_addr(img.addr, &img.bpp, &img.size_line, &img.endian);
	draw_line((t_vec2){400, 300}, (t_vec2){100, 100}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	draw_line((t_vec2){400, 300}, (t_vec2){100, 300}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	draw_line((t_vec2){400, 300}, (t_vec2){100, 700}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	draw_line((t_vec2){400, 300}, (t_vec2){400, 100}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	draw_line((t_vec2){400, 300}, (t_vec2){400, 700}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	// draw_line((t_vec2){400, 300}, (t_vec2){700, 100}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	// draw_line((t_vec2){400, 300}, (t_vec2){700, 300}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	// draw_line((t_vec2){400, 300}, (t_vec2){700, 700}, (int [2]){0xFFFFFF, 0xFFFFFF}, &img);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img.addr, 0, 0);
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
	create_img(data);
	init_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (delete_window(data), free_map(data.map), 0);
}
