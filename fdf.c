/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:06:52 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/10 18:06:55 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_map_size_y(char *file)
{
	int		ret;
	int		fd;
	char	*line;
	size_t		map_size_y;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error();
	ret = get_next_line(fd, &line);
	map_size_y = 0;
	while (ret)
	{
		map_size_y++;
		ret = get_next_line(fd, &line);
	}
	close(fd);
	return (map_size_y);
}

void	malloc_map(int ***map, size_t size_x, size_t size_y)
{
	size_t		i;
	size_t		j;

	j = 0;
	*map = (int **)malloc(sizeof(int *) * size_y);
	if (!(*map))
		handle_error();
	i = 0;
	while (i < size_y)
	{
		(*map)[i] = (int *)malloc(sizeof(int) * size_x);
		if (!((*map)[i]))
		{
			j = 0;
			while (j < i - 1)
			{
				free((*map)[j]);
				j++;
			}
			free(*map);
			handle_error();
		}
		i++;
	}
}

void	print_map(int **map, size_t width, size_t length)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < length)
	{
		j = 0;
		while (j < width)
		{
			printf("%d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

int		deal_key(int key, void *param)
{
	t_mlx_win *mlx_win;

	mlx_win = (t_mlx_win *)param;
	printf("key is %d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
		exit(0);
	}
	if (key == 123)
	{
		//printf("key is %d\n", key);
	}
	return (0);
}

int		round_point(float x)
{
	if ((int)(x * 10) % 10 >= 5)
	{
		//printf("arrondissons. %f\n", x);
		return ((int)x + 1);
	}
	//printf("n'arrondissons pas. %f\n", x);
	return ((int)x);
}

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

void	get_window_dimensions(size_t *dimensions , size_t width, size_t length)
{
	(void)width;
	(void)length;
	(dimensions)[0] = 600;
	(dimensions)[1] = 600;
}

void	*open_window(void *mlx_ptr, size_t *dimensions, char *file)
{
	void	*window;

	window = handle_null(mlx_new_window(mlx_ptr, dimensions[0], dimensions[1], file));
	return (window);
}

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

void	trace_line(t_mlx_win *mlx_win, size_t j, size_t i)
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

void	draw_points(t_mlx_win *mlx_win)
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
			trace_line(mlx_win, y, x);
			x++;
		}
		y++;
	}
}

void	open_mlx(int **map, size_t width, size_t length, char *file, size_t highest)
{
	void	*mlx_ptr;
	void	*window;
	t_mlx_win *mlx_win;
	size_t	dimensions[2];

	mlx_ptr = handle_null(mlx_init());
	mlx_win = (t_mlx_win *)malloc(sizeof(t_mlx_win));
	if (!mlx_win)
		handle_error();
	get_window_dimensions(dimensions, width, length);
	window = open_window(mlx_ptr, dimensions, file);
	mlx_win->mlx_ptr = mlx_ptr;
	mlx_win->window = window;
	mlx_win->map = map;
	mlx_win->map_width = width;
	mlx_win->map_length = length;
	mlx_win->window_width = dimensions[0];
	mlx_win->window_length = dimensions[1];
	mlx_win->rotation_a = 20;
	mlx_win->highest = highest * 20; // 20?
	draw_points(mlx_win);
	mlx_key_hook(window, deal_key, (void *)mlx_win);
	mlx_loop(mlx_ptr);
}

void	test(void)
{
	int	color;

	color = 0xffffff;
	//printf("color is %x\n", color >> 16 & 0xff);
	printf("color is %x\n", color);
	//printf("color is %x\n", color | 0x0000ff);
	printf("color is %x\n", color & 0xff0000);
	printf("color is %x\n", (color & 0xff0000) | 0x0000aa);
	printf("color is %x\n", (color & 0xff0000) | 170);
	printf("color is %x\n", (color & 0xff0000) | (170 << 8));
	//printf("color is %x\n", color | (0x45 << 8));
	//printf("color is %x\n", color | (0x45 << 16));
}

void	parse_file(char *file)
{
	int			ret;
	int			fd;
	size_t		i;
	size_t		j;
	size_t		map_width;
	size_t		map_len;
	char		*line;
	char		**data_ar;
	int			**map;
	size_t		highest;

	test();
	map_width = 0;
	map_len = get_map_size_y(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error();
	ret = get_next_line(fd, &line);
	j = 0;
	highest = 0;
	while (ret)
	{
		//printf("line is '%s'\n", line);
		data_ar = ft_strsplit(line, ' ');
		i = 0;
		if (!map_width)
		{
			while (data_ar[i])
				i++;
			map_width = i;
			//printf("so x size is '%zu' and y size is '%zu'\n", map_width, map_len);
			malloc_map(&map, map_width, map_len);
			i = 0;
		}
		while (i < map_width && data_ar[i])
		{
			//printf("'%d' \n", ft_atoi(data_ar[i]));
			map[j][i] = ft_atoi(data_ar[i]);
			if (ft_atoi(data_ar[i]) > (int)highest)
				highest = ft_atoi(data_ar[i]);
			i++;
		}
		if (i < map_width)
			handle_error();
		printf("\n");
		ret = get_next_line(fd, &line);
		j++;
	}
	close(fd);
	print_map(map, map_width, map_len);
	open_mlx(map, map_width, map_len, file, highest);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		print_usage();
	parse_file(argv[1]);
	return (0);
}

/*


*/