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

void	get_window_dimensions(size_t *dimensions, t_mlx_win *mlx_win)
{
	size_t	map_width;
	size_t	map_length;

	map_width = mlx_win->map_width;
	map_length = mlx_win->map_length;
	(dimensions)[0] = 900;
	(dimensions)[1] = 900;
}

void	tests(t_mlx_win *mlx_win)
{
	t_coords *point_a;
	t_coords *point_b;
	t_coords *point_c;
	t_coords *point_d;
	point_a = (t_coords *)malloc(sizeof(t_coords));
	point_b = (t_coords *)malloc(sizeof(t_coords));
	point_c = (t_coords *)malloc(sizeof(t_coords));
	point_d = (t_coords *)malloc(sizeof(t_coords));
	int	off_x;
	int	off_x_y;
	int	off_y;
	int	off_y_x;
	int segment;

	segment = 200;
	off_x = 22;
	off_x = (int)sqrt((((double)segment * (double)segment) / 2)) ;
	double test = 112.5;
	test = sqrt(test);
	printf("sqrt is %f\n", test);
	printf("off_x is %d\n", off_x);
	off_y = off_x;
	off_x_y = off_x;
	off_y_x = off_x;

	point_a->x = 200;
	point_a->y = 200;

	point_b->x = point_a->x + (off_x * 1) + (off_x_y * 0);
	point_b->y = point_a->y - (off_y * 1) + (off_y_x * 0); // 0: j: len, et 1: i: width
	
	point_c->x = point_a->x + (off_x * 1) + (off_x_y * 1);
	point_c->y = point_a->y - (off_y * 1) + (off_y_x * 1);

	point_d->x = point_a->x + (off_x * 0) + (off_x_y * 1);
	point_d->y = point_a->y - (off_y * 0) + (off_y_x * 1);

	point_a->color = 0xf01707; //red
	point_b->color = 0x07a6f0; // blue
	point_c->color = 0xdb70db; // rose
	point_d->color = 0xe8d909; // yellow

	print_pixel(mlx_win, point_a);
	print_pixel(mlx_win, point_b);
	print_pixel(mlx_win, point_c);
	print_pixel(mlx_win, point_d);

	draw_line(mlx_win, point_a, point_b);
	draw_line(mlx_win, point_b, point_c);
	draw_line(mlx_win, point_c, point_d);
	draw_line(mlx_win, point_a, point_d);

	mlx_win->segment = segment;
	mlx_win->point_a = point_a;
	mlx_win->point_b = point_b;
	mlx_win->point_c = point_c;
	mlx_win->point_d = point_d;

	mlx_win->off_x = off_x;
	mlx_win->off_x_y = off_x_y;
	mlx_win->off_y = off_y;
	mlx_win->off_y_x = off_y_x;
}

void	open_mlx(t_mlx_win *mlx_win, char *file)
{
	void	*mlx_ptr;
	void	*window;
	size_t	dimensions[2];

	mlx_ptr = handle_null(mlx_init());

	get_window_dimensions(dimensions, mlx_win);
	window = handle_null(mlx_new_window(mlx_ptr, dimensions[0], \
		dimensions[1], file));
	mlx_win->mlx_ptr = mlx_ptr;
	mlx_win->window = window;
	mlx_win->window_width = dimensions[0];
	mlx_win->window_length = dimensions[1];
	mlx_win->segment = 30;
	draw_map(mlx_win);
	//tests(mlx_win);
	mlx_key_hook(window, handle_key, (void *)mlx_win);
	mlx_loop(mlx_ptr);
}
