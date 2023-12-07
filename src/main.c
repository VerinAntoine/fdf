/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:57:41 by averin            #+#    #+#             */
/*   Updated: 2023/12/07 11:20:05 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

#define WIDTH 800
#define HEIGHT 600

int	key_hook(int keycode, t_data *param)
{
	if (keycode == XK_Escape)
	{
		mlx_clear_window(param->mlx_ptr, param->window_ptr);
		mlx_loop_end(param->mlx_ptr);
	}
	return (0);
}

int	main(void)
{ 
	t_data	data = {0};

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
