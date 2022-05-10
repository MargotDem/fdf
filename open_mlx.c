/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:38:06 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:38:08 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_offsets(t_mlx_win *mlx_win)
{
	size_t	length;

	length = (int)sqrt((((double)mlx_win->z_offset * \
		(double)mlx_win->z_offset) / 2));
	if (mlx_win->projection == 0)
	{
		mlx_win->x_offset = length + length / 4;
		mlx_win->y_offset = length - length / 4;
		mlx_win->x_y_offset = mlx_win->x_offset;
		mlx_win->y_x_offset = mlx_win->y_offset;
	}
	else if (mlx_win->projection == 1)
	{
		mlx_win->x_offset = length;
		mlx_win->y_offset = mlx_win->x_offset;
		mlx_win->x_y_offset = mlx_win->x_offset;
		mlx_win->y_x_offset = mlx_win->y_offset;
	}
}

void	set_base_point(t_mlx_win *mlx_win, size_t offset)
{
	t_coords	*base_point;

	base_point = (t_coords *)malloc(sizeof(t_coords));
	if (!base_point)
		handle_error();
	base_point->x = 0 + \
		(offset * mlx_win->map_width + offset * mlx_win->map_length) * 0.15;
	base_point->y = mlx_win->window_length - (mlx_win->map_length * offset) - \
		(offset * mlx_win->map_length + offset * mlx_win->map_width + \
		mlx_win->highest * mlx_win->z_offset) * 0.1;
	mlx_win->base_point = base_point;
}

void	set_window_dimensions(t_mlx_win *mlx_win, size_t offset)
{
	size_t	map_width;
	size_t	map_length;
	size_t	window_width;
	size_t	window_length;

	map_width = mlx_win->map_width;
	map_length = mlx_win->map_length;
	window_width = (offset * map_width + offset * map_length) * 1.4;
	window_length = (offset * map_length + offset * map_width + \
		mlx_win->highest * mlx_win->z_offset) * 1.2;
	mlx_win->window_width = window_width;
	mlx_win->window_length = window_length;
	printf("heree 1\n");
}

void	set_dimensions(t_mlx_win *mlx_win)
{
	size_t	offset;

	mlx_win->z_offset = 30;
	printf("highest %d\n", mlx_win->highest);
	offset = (int)sqrt((((double)mlx_win->z_offset * \
		(double)mlx_win->z_offset) / 2));
	if (mlx_win->highest * mlx_win->z_offset + offset * mlx_win->map_width + offset * mlx_win->map_length > 1200)
	{
		mlx_win->z_offset = 30 * 1200 / mlx_win->highest * mlx_win->z_offset + offset * mlx_win->map_width + offset * mlx_win->map_length;
		offset = (int)sqrt((((double)mlx_win->z_offset * \
		(double)mlx_win->z_offset) / 2));
		printf("mlx_win->z_offset %zu\n", mlx_win->z_offset);
		//handle_error();
	}
	set_window_dimensions(mlx_win, offset);
		printf("heree 3 %zu %zu\n", mlx_win->window_length, mlx_win->window_width);
	if (mlx_win->window_length > 1200 || mlx_win->window_width > 1400)
	{
		if (mlx_win->window_length / 1200 > mlx_win->window_width / 1400)
			mlx_win->z_offset = 30 * 1200 / mlx_win->window_length;
		else
			mlx_win->z_offset = 30 * 1400 / mlx_win->window_width;
		if (mlx_win->z_offset == 1)
			mlx_win->z_offset = 2;
		offset = (int)sqrt((((double)mlx_win->z_offset * \
			(double)mlx_win->z_offset) / 2));
		printf("heree 4 %zu %zu   new offset \n", mlx_win->window_length, mlx_win->window_width, );
		set_window_dimensions(mlx_win, offset);
		printf("heree 5 %zu %zu\n", mlx_win->window_length, mlx_win->window_width);
	}
	printf("heree 2\n");
	set_base_point(mlx_win, offset);
}

void	open_mlx(t_mlx_win *mlx_win, char *file)
{
	void	*mlx_ptr;
	void	*window;

	mlx_ptr = handle_null(mlx_init());
	mlx_win->mlx_ptr = mlx_ptr;
	set_dimensions(mlx_win);
	window = handle_null(mlx_new_window(mlx_ptr, mlx_win->window_width, \
		mlx_win->window_length, file));
	mlx_win->window = window;
	draw_map(mlx_win);
	mlx_key_hook(window, handle_key, (void *)mlx_win);
	mlx_loop(mlx_ptr);
}
