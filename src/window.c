/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:01:11 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 10:11:31 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	delete_window(t_data data)
{
	mlx_clear_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	free(data.mlx_ptr);
}
