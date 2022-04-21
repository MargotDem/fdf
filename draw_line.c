/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:52:36 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:52:38 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		pick_color_point(size_t highest, t_coords *point)
{
	int	diff;
	int	color;
	int	gb_value;

	color = 0xffffff; // white
	if (highest != 0)
	{
		//ff4242
		diff = point->floor - point->y;
		gb_value = (diff * 255) / highest;
		color = (color & 0xff0000) | gb_value | gb_value << 8;
	}
	point->color = color;
}

int		pick_color_gradient(int y, t_coords *point_a, t_coords *point_b)
{
	int color;
	int	diff_y;
	int	diff_color;
	int	gb_value;
	int	gb_value_a;

	color = point_a->color;
	gb_value_a = point_a->color & 0xff;
	diff_y = ft_abs(point_a->y - point_b->y);
	diff_color = point_a->color & 0xff - point_b->color & 0xff;
	gb_value = (ft_abs(point_a->y - y) * ft_abs(diff_color) / diff_y);
	if (diff_color > 0)
		color = (color & 0xff0000) | gb_value_a - gb_value | \
			((gb_value_a - gb_value) << 8);
	else
		color = (color & 0xff0000) | gb_value_a + gb_value | \
			((gb_value_a + gb_value) << 8);
	return (color);
}

void	draw_line(t_mlx_win *mlx_win, t_coords *point_a, t_coords *point_b)
{
	int	x;
	int	y;
	int	color;

	pick_color_point(mlx_win->highest, point_a);
	pick_color_point(mlx_win->highest, point_b);
	print_pixel(mlx_win, point_a);
	x = point_a->x;
	y = point_a->y;
	if (point_b->x - point_a->x >= ft_abs(point_b->y - point_a->y))
	{
		while (x < point_b->x)
		{
			y = round_point(((float)(point_b->y - point_a->y) / (float)(point_b->x - point_a->x)) * (x - point_a->x) + point_a->y + 0.5);
			color = pick_color_gradient(y, point_a, point_b);
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
			x++;
		}
	}
	else
	{
		if (point_b-> y > point_a->y)
		{
			while (y < point_b->y)
			{
				x = round_point(point_a->x + (y - 0.5 - point_a->y) * (  (float)(point_b->x - point_a->x) / (float)(point_b->y - point_a->y)    ));
				color = pick_color_gradient(y, point_a, point_b);
				mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
				y++;
			}
		}
		else
		{
			while (y > point_b->y)
			{
				x = round_point(point_a->x + (y - 0.5 - point_a->y) * (  (float)(point_b->x - point_a->x) / (float)(point_b->y - point_a->y)    ));
				color = pick_color_gradient(y, point_b, point_a);
				//color = 0x00d443;
				mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
				y--;
			}
		}
	}
	print_pixel(mlx_win, point_b);
}
