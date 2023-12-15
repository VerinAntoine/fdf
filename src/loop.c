/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:02:15 by averin            #+#    #+#             */
/*   Updated: 2023/12/15 13:01:45 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_next(int keycode, t_data *data)
{
	if (keycode == XK_Up)
		translate(data->map, (t_vec3){-1, 0, 0});
	if (keycode == XK_Down)
		translate(data->map, (t_vec3){1, 0, 0});
	if (keycode == XK_Left)
		translate(data->map, (t_vec3){0, 0, -1});
	if (keycode == XK_Right)
		translate(data->map, (t_vec3){0, 0, 1});
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == XK_a)
		data->view->deg_x += 5;
	if (keycode == XK_d)
		data->view->deg_x -= 5;
	if (keycode == XK_w)
		data->view->deg_z += 5;
	if (keycode == XK_s)
		data->view->deg_z -= 5;
	if (keycode == XK_q)
		data->view->deg_y += 5;
	if (keycode == XK_e)
		data->view->deg_y -= 5;
	if (keycode == XK_r)
		data->view->scale += 1;
	if (keycode == XK_f)
		data->view->scale -= 1;
	if (keycode == XK_t)
		data->view->height += 0.1f;
	if (keycode == XK_g)
		data->view->height -= 0.1f;
	return (handle_key_next(keycode, data));
}

int	handle_destroy(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	loop_hook(t_data *data)
{
	create_img(*data);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_hook(data->win_ptr, DestroyNotify, 0, handle_destroy, data);
	mlx_key_hook(data->win_ptr, handle_key, data);
	mlx_loop_hook(data->mlx_ptr, loop_hook, data);
}
