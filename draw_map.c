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

void	set_base_point(t_mlx_win *mlx_win)
{
	t_coords	*base_point;

	base_point = (t_coords *)malloc(sizeof(t_coords));
	if (!base_point)
		handle_error();
	base_point->x = 50;
	base_point->y = 700;
	mlx_win->base_point = base_point;
}

void	set_offsets(t_mlx_win *mlx_win)
{

	if (mlx_win->projection == 0)
	{
		// z_offset of 10 and 20 work but not 15 what is the name of jesus christ is going on (only for tests 3 and 4 tho)
		mlx_win->z_offset = 20; // 20?
		mlx_win->x_offset = 25; // 25?
		mlx_win->y_offset = 15; // 15?
	}
	else if (mlx_win->projection == 1)
	{
		// z_offset of 10 and 20 work but not 15 what is the name of jesus christ is going on (only for tests 3 and 4 tho)
		mlx_win->z_offset = 20; // 20?
		mlx_win->x_offset = 20; // 25?
		mlx_win->y_offset = 20; // 15?
	}
}

size_t	get_x(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	x;

	x = (mlx_win->base_point->x + (mlx_win->x_offset * i)) + (mlx_win->x_offset * j);
	return (x);
}

size_t	get_y_floor(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	y;

	// (mlx_win->y_offset * i) actually another offset. == yoffset if symmetric losange ie if xoffset == yoffset
	y = mlx_win->base_point->y - (mlx_win->y_offset * i) + (mlx_win->y_offset * j);
	return (y);
}


size_t	get_y(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	y;

	y = get_y_floor(mlx_win, i, j) - (mlx_win->map[j][i] * mlx_win->z_offset);
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
	free(point_a);
	free(point_b);
}


void	draw_grid(t_mlx_win *mlx_win)
{
	int i;
	int j;
	int color;
	color = 0xe0e0e0;

	i = 0;
	while (i < 600)
	{
		j = 0;
		while (j < 600)
		{
			if ((i % 20 == 0) || (j % 20 == 0))
				mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, i, j, color);
			j++;
		}
		i++;
	}
}

void	erase_map(t_mlx_win *mlx_win)
{
	int i;
	int j;
	int color;
	color = 0x000000;

	i = 0;
	while (i < 900)
	{
		j = 0;
		while (j < 900)
		{
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_mlx_win *mlx_win)
{
	size_t		x;
	size_t		y;

	set_offsets(mlx_win);
	set_base_point(mlx_win);
	//draw_grid(mlx_win);
	printf("hello\n");
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
