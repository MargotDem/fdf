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
		printf("segment is %zu\n", mlx_win->segment);
		int max = mlx_win->segment;
		static int plus_off_x_y = 0;
		static int plus_off_y_x = 1;
		static int plus_dist_x = 0;
		if (plus_off_x_y)
		{
			mlx_win->off_x_y += 10;
			if (mlx_win->off_x_y >= max)
				plus_off_x_y = 0;
		}
		else
		{
			mlx_win->off_x_y -= 10;
			if (mlx_win->off_x_y <= -max)
				plus_off_x_y = 1;
		}
		if (plus_off_y_x)
		{
			mlx_win->off_y_x += 10;
			if (mlx_win->off_y_x >= max)
				plus_off_y_x = 0;
		}
		else
		{
			mlx_win->off_y_x -= 10;
			if (mlx_win->off_y_x <= -max)
				plus_off_y_x = 1;
		}




		int dist_x;
		dist_x = mlx_win->point_e->x - mlx_win->point_a->x;
		printf("off_x_y is %d and off_y_x is %d and idst is %d and max is %d\n", mlx_win->off_x_y, mlx_win->off_y_x, dist_x, max);
		//int dist_x_d = mlx_win->point_e->x - mlx_win->point_d->x;

		if (plus_dist_x)
		{
			dist_x += 10;
			mlx_win->point_a->x -= 10;
			//mlx_win->point_d->x -= 10;
			mlx_win->point_a->y = mlx_win->point_e->y - (sqrt((max / 2) * (max / 2) - dist_x * dist_x));
			//mlx_win->point_d->y = mlx_win->point_e->y - (sqrt((max / 2) * (max / 2) - dist_x_d * dist_x_d));
			if (dist_x >= (max / 2))
				plus_dist_x = 0;
		}
		else
		{
			dist_x -= 10;
			mlx_win->point_a->x += 10;
			//mlx_win->point_d->x += 10;
			mlx_win->point_a->y = mlx_win->point_e->y - (sqrt((max / 2) * (max / 2) - dist_x * dist_x));
			//mlx_win->point_d->y = mlx_win->point_e->y - (sqrt((max / 2) * (max / 2) - dist_x_d * dist_x_d));
			if (dist_x <= -(max / 2))
				plus_dist_x = 1;
		}
		

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
