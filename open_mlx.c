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

	length = (int)sqrt((((double)mlx_win->segment * (double)mlx_win->segment) / 2));
	if (mlx_win->projection == 0)
	{
		mlx_win->z_offset = mlx_win->segment; // 20?
		//mlx_win->x_offset = 25; // 25?
		//mlx_win->y_offset = 15; // 15?
		mlx_win->x_offset = length + length / 4;
		mlx_win->y_offset = length - length / 4;
		mlx_win->x_y_offset = mlx_win->x_offset;
		mlx_win->y_x_offset = mlx_win->y_offset;
	}
	else if (mlx_win->projection == 1)
	{
		mlx_win->z_offset = mlx_win->segment; // 20?
		//mlx_win->x_offset = 20; // 25?
		mlx_win->x_offset = length;
		mlx_win->y_offset = mlx_win->x_offset; // 15?
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
	base_point->x = 0 + (offset * mlx_win->map_width + offset * mlx_win->map_length) * 0.15;
	base_point->y = mlx_win->window_length - (mlx_win->map_length * offset) - \
		(offset * mlx_win->map_length + offset * mlx_win->map_width + mlx_win->highest * mlx_win->segment) * 0.1;
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
	window_length = (offset * map_length + offset * map_width + mlx_win->highest * mlx_win->segment) * 1.2;
	mlx_win->window_width = window_width;
	mlx_win->window_length = window_length;
}

void	set_dimensions(t_mlx_win *mlx_win)
{
	size_t	offset;

	mlx_win->segment = 30;
	offset = (int)sqrt((((double)mlx_win->segment * (double)mlx_win->segment) / 2));
	set_window_dimensions(mlx_win, offset);

	if (mlx_win->window_length > 1200 || mlx_win->window_width > 1400)
	{
		if (mlx_win->window_length / 1200 > mlx_win->window_width / 1400)
		{
			mlx_win->segment = 30 * 1200 / mlx_win->window_length;
			if (mlx_win->segment == 1)
				mlx_win->segment = 2;
			offset = (int)sqrt((((double)mlx_win->segment * (double)mlx_win->segment) / 2));
			printf("and here segment is %zu\n", mlx_win->segment);
			set_window_dimensions(mlx_win, offset);
		}
		else
		{
			mlx_win->segment = 30 * 1400 / mlx_win->window_width;
			if (mlx_win->segment == 1)
				mlx_win->segment = 2;
			offset = (int)sqrt((((double)mlx_win->segment * (double)mlx_win->segment) / 2));
			printf("hehe segment is %zu\n", mlx_win->segment);
			set_window_dimensions(mlx_win, offset);
		}
	}
	set_base_point(mlx_win, offset);
}  

void	tests(t_mlx_win *mlx_win)
{
	t_coords *point_a;
	t_coords *point_b;
	t_coords *point_c;
	t_coords *point_d;
	t_coords *point_e;
	point_a = (t_coords *)malloc(sizeof(t_coords));
	point_b = (t_coords *)malloc(sizeof(t_coords));
	point_c = (t_coords *)malloc(sizeof(t_coords));
	point_d = (t_coords *)malloc(sizeof(t_coords));
	point_e = (t_coords *)malloc(sizeof(t_coords));
	int	off_x;
	int	off_x_y;
	int	off_y;
	int	off_y_x;
	int segment;

	segment = 200;
	off_x = 22;
	off_x = (int)sqrt((((double)segment * (double)segment) / 2)) ;
	printf("off_x is %d\n", off_x);
	off_y = off_x;
	off_x_y = off_x;
	off_y_x = off_x;

	point_a->x = 400;
	point_a->y = 800;

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
	point_e->color = 0xf7143e; // pinkish red

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
	mlx_win->point_e = point_e;

	mlx_win->off_x = off_x;
	mlx_win->off_x_y = off_x_y;
	mlx_win->off_y = off_y;
	mlx_win->off_y_x = off_y_x;

	point_e->x = point_a->x + (point_d->x - point_a->x) / 2;
	point_e->y = point_a->y + (point_d->y - point_a->y) / 2;
	//point_e->x = 200;
	//point_e->y = 200;
	print_pixel(mlx_win, point_e);
}

void	tests2(void)
{
	printf("holaaaa\n");
	int max = 200;
	int i = 0;
	int plus = 1;
	int curseur = 0;

	while (i < 40)
	{
		if (plus)
		{
			curseur += 20;
			if (curseur == max)
				plus = 0;
		}
		else
		{
			curseur -= 20;
			if (curseur == -max)
				plus = 1;
		}
		printf("curseur is %d\n", curseur);
		i++;
	}
}

void	open_mlx(t_mlx_win *mlx_win, char *file)
{
	void	*mlx_ptr;
	void	*window;

	mlx_ptr = handle_null(mlx_init());
	set_dimensions(mlx_win);
	//window = handle_null(mlx_new_window(mlx_ptr, mlx_win->window_width, mlx_win->window_length, file));
	window = handle_null(mlx_new_window(mlx_ptr, 1000, 1200, file));
	mlx_win->mlx_ptr = mlx_ptr;
	mlx_win->window = window;
	//draw_map(mlx_win);
	tests(mlx_win);
	//tests2();
	mlx_key_hook(window, handle_key, (void *)mlx_win);
	mlx_loop(mlx_ptr);
}
