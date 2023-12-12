/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:02:42 by averin            #+#    #+#             */
/*   Updated: 2023/12/12 09:14:37 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
}	t_data;

int	create_window(t_data *data);

#endif
