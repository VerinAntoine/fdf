/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:41 by averin            #+#    #+#             */
/*   Updated: 2023/12/09 09:16:46 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_matrix
{
	t_point	i;
	t_point	j;
	t_point	k;
}	t_matrix;

typedef struct s_map
{
	t_point	*points;
	int		width;
	int		heigth;
}	t_map;

typedef struct s_view
{
	float	deg_x;
	float	deg_y;
	float	deg_z;
	int		scale;
	float	height;
}	t_view;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*window_ptr;
	t_map	*map;
	t_view	*view;
}	t_data;

t_map	*parse(char *filename);
void	print_line(t_point p0, t_point p1, t_data data);

// t_vector2	*iso_projection(t_vector3 *vector);
t_point	*get_point(t_map *map, int x, int y);
void	free_map(t_map *map);
void	print_map(t_map *map);

#endif
