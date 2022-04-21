/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:39:23 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:39:24 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		handle_key(int key, void *param)
{
	t_mlx_win *mlx_win;

	mlx_win = (t_mlx_win *)param;
	printf("key is %d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
		exit(0);
	}
	if (key == 123) // <
	{
		//printf("key is %d\n", key);
		mlx_win->off_x_y -=20;
		mlx_win->off_y_x +=20;
		printf("off_x_y is %d and off_y_x is %d\n", mlx_win->off_x_y, mlx_win->off_y_x);


		mlx_win->point_b->x = mlx_win->point_a->x + (mlx_win->off_x * 1) + (mlx_win->off_x_y * 0);
		mlx_win->point_b->y = mlx_win->point_a->y - (mlx_win->off_y * 1) + (mlx_win->off_y_x * 0); // 0: j: len, et 1: i: width
		
		mlx_win->point_c->x = mlx_win->point_a->x + (mlx_win->off_x * 1) + (mlx_win->off_x_y * 1);
		mlx_win->point_c->y = mlx_win->point_a->y - (mlx_win->off_y * 1) + (mlx_win->off_y_x * 1);

		mlx_win->point_d->x = mlx_win->point_a->x + (mlx_win->off_x * 0) + (mlx_win->off_x_y * 1);
		mlx_win->point_d->y = mlx_win->point_a->y - (mlx_win->off_y * 0) + (mlx_win->off_y_x * 1);

		print_pixel(mlx_win, mlx_win->point_a);
		print_pixel(mlx_win, mlx_win->point_b);
		print_pixel(mlx_win, mlx_win->point_c);
		print_pixel(mlx_win, mlx_win->point_d);

		draw_line(mlx_win, mlx_win->point_a, mlx_win->point_b);
		draw_line(mlx_win, mlx_win->point_b, mlx_win->point_c);
		draw_line(mlx_win, mlx_win->point_c, mlx_win->point_d);
		draw_line(mlx_win, mlx_win->point_a, mlx_win->point_d);
	}
	if (key == 35) // p
	{
		erase_map(mlx_win);
		if (mlx_win->projection == 0)
		{
			mlx_win->projection = 1;
		}
		else if (mlx_win->projection == 1)
		{
			mlx_win->projection = 0;
		}
		draw_map(mlx_win);
		//printf("key is %d\n", key);
	}
	if (key == 3)//f
	{
		size_t	tmp;
		size_t	i;
		size_t	j;

		erase_map(mlx_win);
		j = 0;
		while (j < mlx_win->map_length)
		{
			i = 0;
			while (i < mlx_win->map_width / 2)
			{
				tmp = mlx_win->map[j][i];
				mlx_win->map[j][i] = mlx_win->map[j][mlx_win->map_width - i - 1];
				mlx_win->map[j][mlx_win->map_width - i - 1] = tmp;
				i++;
			}
			j++;
		}
		draw_map(mlx_win);
	}
	if (key == 5)//g
	{
		int	*tmp;
		size_t	j;

		erase_map(mlx_win);
		j = 0;
		while (j < mlx_win->map_length / 2)
		{
			tmp = mlx_win->map[j];
			mlx_win->map[j] = mlx_win->map[mlx_win->map_length - j - 1];
			mlx_win->map[mlx_win->map_length - j - 1] = tmp;
			j++;
		}
		draw_map(mlx_win);
	}
	if (key == 4)//h
	{
		
	}
	return (0);
}
