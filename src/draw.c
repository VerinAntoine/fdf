/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:22:02 by averin            #+#    #+#             */
/*   Updated: 2023/12/14 17:24:20 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/**
 * Draw a straight line on x axis
 * @param c Array of the coordonates of the line [a.y, b.y, a.x, a.y]
 * @param s The direction of the line
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_straight_line_x(int c[4], int s, int *colors, t_img *img)
{
	while (c[0] != c[1])
	{
		img_pixel_put(img, c[0], c[2], lerp_color(colors, c[3], c[1], c[0]));
		c[0] += s;
	}
}

/**
 * Draw a straight line on y axis
 * @param c Array of the coordonates of the line [a.x, b.x, a.y, a.x]
 * @param s The direction of the line
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_straight_line_y(int c[4], int s, int *colors, t_img *img)
{
	while (c[0] != c[1])
	{
		img_pixel_put(img, c[2], c[0], lerp_color(colors, c[3], c[1], c[0]));
		c[0] += s;
	}
}

/**
 * Draw a diagonal line on the x octant
 * @param c Array of the coordonates of the line [a.x, b.x, a.y, a.x]
 * @param ds Array of slope and sign of the line [dx, dy, sx, sy]
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_diagonal_line_x(int c[4], int ds[4], int *colors, t_img *img)
{
	int	slope;
	int	error;

	slope = 2 * ds[1];
	error = -ds[0];
	while (c[0] != c[1])
	{
		c[0] += ds[2];
		img_pixel_put(img, c[0], c[2], lerp_color(colors, c[3], c[1], c[0]));
		error += slope;
		if (error >= 0)
		{
			c[2] += ds[3];
			error += -2 * ds[0];
		}
	}
}

/**
 * Draw a diagonal line on the y octant
 * @param c Array of the coordonates of the line [a.y, b.y, a.x, a.y]
 * @param ds Array of slope and sign of the line [dx, dy, sx, sy]
 * @param colors Array of the gradient to create on the line
 * @param img Pointer to image in wich draw the line
*/
static void	draw_diagonal_line_y(int c[4], int ds[4], int *colors, t_img *img)
{
	int	slope;
	int	error;

	slope = 2 * ds[0];
	error = -ds[1];
	while (c[0] != c[1])
	{
		c[0] += ds[3];
		img_pixel_put(img, c[2], c[0], lerp_color(colors, c[3], c[1], c[0]));
		error += slope;
		if (error >= 0)
		{
			c[2] += ds[2];
			error += -2 * ds[1];
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
void	draw_line(t_vec3 a, t_vec3 b, t_map map, t_img *img)
{
	int	ds[4];
	int	*colors;

	colors = get_colors(map, a.y, b.y);
	printf("line from %f %f %f to %f %f %f\n", a.x, a.y, a.z, b.x, b.y, b.z);
	printf("dl: colors: %x %x\n", colors[0], colors[1]);
	ds[0] = ft_abs(a.x - b.x);
	ds[1] = ft_abs(a.z - b.z);
	ds[2] = -ft_sign(a.x - b.x);
	ds[3] = -ft_sign(a.z - b.z);
	if (ds[1] == 0)
		draw_straight_line_x((int [4]){a.x, b.x, a.z, a.x}, ds[2], colors, img);
	else if (ds[0] == 0)
		draw_straight_line_y((int [4]){a.z, b.z, a.x, a.z}, ds[3], colors, img);
	else if (ds[0] >= ds[1])
		draw_diagonal_line_x((int [4]){a.x, b.x, a.z, a.x}, ds, colors, img);
	else
		draw_diagonal_line_y((int [4]){a.z, b.z, a.x, a.z}, ds, colors, img);
}
