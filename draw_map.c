/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:49:43 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:49:45 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_line2(t_mlx_win *mlx_win, size_t j, size_t i, t_coords *point_a)
{
	t_coords	*point_b;

	point_b = (t_coords *)malloc(sizeof(t_coords));
	if (!point_b)
		handle_error();
	if (i != mlx_win->map_width - 1)
	{
		point_b->x = get_x(mlx_win, i + 1, j);
		point_b->y = get_y(mlx_win, i + 1, j);
		point_b->floor = get_y_floor(mlx_win, i + 1, j);
		draw_line(mlx_win, point_a, point_b);
	}
	if (j != mlx_win->map_length - 1)
	{
		point_b->x = get_x(mlx_win, i, j + 1);
		point_b->y = get_y(mlx_win, i, j + 1);
		point_b->floor = get_y_floor(mlx_win, i, j + 1);
		draw_line(mlx_win, point_a, point_b);
	}
	free(point_a);
	free(point_b);
}

void	make_line(t_mlx_win *mlx_win, size_t j, size_t i)
{
	size_t		x;
	size_t		y;
	size_t		floor;
	t_coords	*point_a;

	x = get_x(mlx_win, i, j);
	y = get_y(mlx_win, i, j);
	floor = get_y_floor(mlx_win, i, j);
	point_a = (t_coords *)malloc(sizeof(t_coords));
	if (!point_a)
		handle_error();
	point_a->x = x;
	point_a->y = y;
	point_a->floor = floor;
	if (mlx_win->map_width == 1 && mlx_win->map_length == 1)
	{
		point_a->color = 0xffffff;
		print_pixel(mlx_win, point_a);
	}
	make_line2(mlx_win, j, i, point_a);
}

void	draw_map(t_mlx_win *mlx_win)
{
	size_t		x;
	size_t		y;

	set_offsets(mlx_win);
	y = 0;
	while (y < mlx_win->map_length)
	{
		x = 0;
		while (x < mlx_win->map_width)
		{
			make_line(mlx_win, y, x);
			x++;
		}
		y++;
	}
}
