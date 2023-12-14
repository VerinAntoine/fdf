/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:02:42 by averin            #+#    #+#             */
/*   Updated: 2023/12/14 15:16:15 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft.h"
# include "mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define AXIS_X 'x'
# define AXIS_Y 'y'
# define AXIS_Z 'z'

typedef struct	s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct	s_matrix
{
	t_vec3	i;
	t_vec3	j;
	t_vec3	k;
}	t_matrix;

typedef struct	s_map
{
	t_vec3	*points;
	size_t	width;
	size_t	height;
	int		min_height;
	int		max_height;
}	t_map;

typedef struct	t_img
{
	void	*addr;
	char	*content;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
}	t_data;

int		create_window(t_data *data);
void	delete_window(t_data data);
void	img_pixel_put(t_img *img, int x, int y, int color);

void	draw_line(t_vec2 a, t_vec2 b, int colors[2], t_img *img);

void	init_hook(t_data *data);

void	rotate(t_map *map, float deg, char axis);
void	translate(t_map *map, t_vec3 v);
void	scale(t_map *map, t_vec3 v);

int		lerp_color(int colors[2], int start, int end, int current);

t_map	*parse_map(char *filename);

t_vec3	*get_point(t_map *map, size_t x, size_t y);
void	free_map(t_map *map);
void	calibrate_map(t_map *map);

#endif
