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

void		pick_color(size_t highest, t_coords *point)
{
	(void)point;
	//printf("floor %d and y %d\n", point->floor, point->y);
	int	max;
	int	diff;
	int	color;

	max = highest;
	color = 0xffffff;
	diff = point->floor - point->y;
	color = (color & 0xff0000) | ((diff * 255) / max);
	color = color | (((diff * 255) / max) << 8);
	printf("color is %x\n", color);
	point->color = color;
}

int		pick_color2(int y, t_coords *point_a, t_coords *point_b)
{
	int color;
	int	diff_y;
	int	diff_color;

	color = point_a->color;
	(void)y;
	(void)point_b;
	diff_y = ft_abs(point_a->y - point_b->y);
	diff_color = point_a->color & 0xff - point_b->color & 0xff;
	if (diff_color > 0)
	{
		color = (color & 0xff0000) | (point_a->color & 0xff) - (ft_abs(point_a->y - y) * ft_abs(diff_color) / diff_y);
		color = color | (((point_a->color & 0xff) - (ft_abs(point_a->y - y) * ft_abs(diff_color) / diff_y)) << 8);
	}
	else
	{
		color = (color & 0xff0000) | (point_a->color & 0xff) + (ft_abs(point_a->y - y) * ft_abs(diff_color) / diff_y);
		color = color | (((point_a->color & 0xff) + (ft_abs(point_a->y - y) * ft_abs(diff_color) / diff_y)) << 8);
	}
	return (color);
}

void	draw_line(t_mlx_win *mlx_win, t_coords *point_a, t_coords *point_b)
{
	int	x;
	int	y;
	int	color;

	//mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, point_a->x, point_a->y, 0xf22233);
	pick_color(mlx_win->highest, point_a);
	pick_color(mlx_win->highest, point_b);
	mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, point_a->x, point_a->y, point_a->color);
	x = point_a->x;
	y = point_a->y;
	if (point_b->x - point_a->x >= ft_abs(point_b->y - point_a->y))
	{
		while (x < point_b->x)
		{
			y = round_point(((float)(point_b->y - point_a->y) / (float)(point_b->x - point_a->x)) * (x - point_a->x) + point_a->y + 0.5);
			color = pick_color2(y, point_a, point_b);
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
				color = pick_color2(y, point_a, point_b);
				mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
				y++;
			}
		}
		else
		{
			while (y > point_b->y)
			{
				x = round_point(point_a->x + (y - 0.5 - point_a->y) * (  (float)(point_b->x - point_a->x) / (float)(point_b->y - point_a->y)    ));
				color = pick_color2(y, point_a, point_b);
				mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, color);
				y--;
			}
		}
	}
	mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, point_b->x, point_b->y, point_b->color);
}
