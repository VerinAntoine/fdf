/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:02:41 by averin            #+#    #+#             */
/*   Updated: 2023/11/23 18:07:27 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*window_ptr;
}	t_data;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_line
{
	t_point	*a;
	t_point	*b;
}	t_line;

typedef struct s_line_data
{
	t_line	*line;
	t_data	*data;
}	t_line_data;

void	print_line(t_line *line, t_data *data);

#endif
