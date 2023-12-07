/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:41 by averin            #+#    #+#             */
/*   Updated: 2023/12/07 11:20:35 by averin           ###   ########.fr       */
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
# define HEIGHT 800

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	u;
	int	z;
}	t_point;

typedef struct s_map
{
	t_point	*points;
	int		width;
	int		heigth;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*window_ptr;
	t_map	*map;
}	t_data;

t_map	*parse(char *filename);
void	print_line(t_point p0, t_point p1, t_data data);

// t_vector2	*iso_projection(t_vector3 *vector);
t_point	*get_point(t_map *map, int x, int y);
void	free_map(t_map *map);
void	print_map(t_map *map);

#endif
