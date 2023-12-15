/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:01:11 by averin            #+#    #+#             */
/*   Updated: 2023/12/15 16:33:16 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Create the window
 * @param data The data of fdf
 * @return TRUE if the window is created, FALSE otherwise
 */
int	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (FALSE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FdF");
	if (!data->win_ptr)
		return (free(data->mlx_ptr), FALSE);
	return (TRUE);
}

/**
 * Delete the window
 * @param data The data of fdf
 */
void	delete_window(t_data data)
{
	mlx_clear_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

/**
 * Put a pixel in the image
 * @param img The image in wich put the pixel
 * @param x The x coordonate of the pixel
 * @param y The y coordonate if the pixel
 * @param color The color of the pixel
 */
void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->content + (y * img->size_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

/**
 * Create and draw the image
 * @param data The data of fdf
 */
void	create_img(t_data data)
{
	t_img	img;

	img.addr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	if (!img.addr)
		return ;
	img.content = mlx_get_data_addr(img.addr, &img.bpp, &img.size_line,
			&img.endian);
	draw_fdf(data, &img);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img.addr, 0, 0);
	mlx_destroy_image(data.mlx_ptr, img.addr);
}
