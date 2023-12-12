/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:02:15 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 13:37:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	destroy(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

void	init_hook(t_data *data)
{
	mlx_key_hook(data->win_ptr, handle_key, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, destroy, data);
}
