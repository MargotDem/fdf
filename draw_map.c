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

void	get_base_point(t_mlx_win *mlx_win)
{
	t_coords	*base_point;

	base_point = (t_coords *)malloc(sizeof(t_coords));
	if (!base_point)
		handle_error();
	base_point->x = 50;
	base_point->y = 400;
	mlx_win->base_point = base_point;
}

size_t	get_x(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	x;

	x = (mlx_win->base_point->x + (25 * i)) + (mlx_win->rotation_a * j);
	return (x);
}

size_t	get_y_floor(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	y;

	y = mlx_win->base_point->y - (15 * i) + (15 * j);
	return (y);
}


size_t	get_y(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	y;

	//y = mlx_win->base_point->y - (15 * i) + (15 * j) - (mlx_win->map[j][i] * 20);
	y = get_y_floor(mlx_win, i, j) - (mlx_win->map[j][i] * 20);
	return (y);
}


void	make_line(t_mlx_win *mlx_win, size_t j, size_t i)
{
	size_t 		x;
	size_t 		y;
	size_t 		floor;
	t_coords	*point_a;
	t_coords	*point_b;

	mlx_win->base_point->y = mlx_win->base_point->y;
	x = get_x(mlx_win, i, j);
	y = get_y(mlx_win, i, j);
	floor = get_y_floor(mlx_win, i, j);
	point_a = (t_coords *)malloc(sizeof(t_coords));
	if (!point_a)
		handle_error();
	point_b = (t_coords *)malloc(sizeof(t_coords));
	if (!point_b)
		handle_error();
	point_a->x = x;
	point_a->y = y;
	point_a->floor = floor;
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
}

void	draw_map(t_mlx_win *mlx_win)
{
	size_t		x;
	size_t		y;

	get_base_point(mlx_win);
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
