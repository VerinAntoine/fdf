/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:00:56 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 12:02:51 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char const *argv[])
{
	t_data	data;

	if (argc != 2)
		return (ft_dprintf(2, "Usage: %s <file.fdf>\n", argv[0]), 0);
	
	return 0;
}
