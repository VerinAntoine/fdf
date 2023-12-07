/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:35:39 by averin            #+#    #+#             */
/*   Updated: 2023/12/05 14:41:57 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector2	*create_vector2(int x, int y)
{
	t_vector2	*vector;

	vector = ft_calloc(1, sizeof(t_vector2));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

void	mult_vector2(t_vector2 *a, t_vector2 *b)
{
	t_vector2	*result;

	result = create_vector2(0, 0);
	result->x = a->x * b->y - b->x * a->y;
}
