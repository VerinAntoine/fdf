/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:22:02 by averin            #+#    #+#             */
/*   Updated: 2023/12/13 13:14:10 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Draw a straight line on x axis
 * @param c Array of the coordonates (x from, x to and y) of the line
 * @param s The direction of the line
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_straight_line_x(int c[3], int s, int colors[2], t_img *img)
{
	(void)colors;
	while (c[0] != c[1])
	{
		img_pixel_put(img, c[2], c[0], 0xFFFFFF);
		c[0] += s;
	}
}

/**
 * Draw a straight line on y axis
 * @param c Array of the coordonates (y from, y to and x) of the line
 * @param s The direction of the line
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_straight_line_y(int c[3], int s, int colors[2], t_img *img)
{
	(void)colors;
	while (c[0] != c[1])
	{
		img_pixel_put(img, c[0], c[0], 0xFFFFFF);
		c[0] += s;
	}
}

/**
 * Draw a diagonal line on the x octant
 * @param c Array of the coordonates of the line
 * @param ds Array of slope and sign of the line
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_diagonal_line_x(int c[3], int ds[4], int colors[2], t_img *img)
{
	int	slope;
	int	error;

	(void)colors;
	slope = 2 * ds[1];
	error = -ds[0];
	while (c[0] != c[1])
	{
		c[0] += ds[3];
		img_pixel_put(img, c[2], c[0], 0xFFFFFF);
		error += slope;
		if (error >= 0)
		{
			c[2] += ds[3];
			error += -2 * ds[2];
		}
	}
}

/**
 * Draw a diagonal line on the y octant
 * @param c Array of the coordonates of the line
 * @param ds Array of slope and sign of the line
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_diagonal_line_y(int c[3], int ds[4], int colors[2], t_img *img)
{
	int	slope;
	int	error;

	(void)colors;
	slope = 2 * ds[1];
	error = -ds[0];
	while (c[0] != c[1])
	{
		c[0] += ds[3];
		img_pixel_put(img, c[0], c[2], 0xFFFFFF);
		error += slope;
		if (error >= 0)
		{
			c[2] += ds[3];
			error += -2 * ds[2];
		}
	}
}

/**
 * Draw a line on an image
 * @param a position of the first point
 * @param b position of the second point
 * @param colors Array of two colors for create a gradient on the line
 * @param img Pointer to image in wich draw the line
*/
void	draw_line(t_vec2 a, t_vec2 b, int colors[2], t_img *img)
{
	int	ds[4];

	ds[0] = ft_abs(a.x - b.x);
	ds[1] = ft_abs(a.y - b.y);
	ds[2] = -ft_sign(a.x - b.x);
	ds[3] = -ft_sign(a.y - b.y);
	if (ds[1] == 0)
		draw_straight_line_x((int [3]){a.x, b.x, a.y}, ds[2], colors, img);
	else if (ds[0] == 0)
		draw_straight_line_y((int [3]){a.y, b.y, a.x}, ds[3], colors, img);
	else if (ds[0] >= ds[1])
		draw_diagonal_line_x((int [3]){a.x, b.x, a.y}, ds, colors, img);
	else
		draw_diagonal_line_y((int [3]){a.y, b.y, a.x}, ds, colors, img);
}
