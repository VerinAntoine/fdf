/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:00:56 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 13:36:03 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_dprintf(2, "Usage: %s <file.fdf>\n", argv[0]), -1);
	data.map = parse_map(argv[1]);
	if (!data.map)
		return (-2);
	if (!create_window(&data))
		return (ft_dprintf(2, "Couldn't create window\n"), -3);
	init_hook(&data);
	mlx_loop(data.mlx_ptr);
	return (delete_window(data), free_map(data.map), 0);
}
