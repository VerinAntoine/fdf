/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:02:42 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 13:35:52 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft.h"
# include "mlx.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct	s_map
{
	t_vec3	*points;
	size_t	width;
	size_t	height;
	int		min_height;
	int		max_height;
}	t_map;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
}	t_data;

int		create_window(t_data *data);
void	delete_window(t_data data);

void	init_hook(t_data *data);

t_map	*parse_map(char *filename);
t_vec3	*get_point(t_map *map, size_t x, size_t y);
void	free_map(t_map *map);

#endif
