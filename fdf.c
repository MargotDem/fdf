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
	if (key == 53)
	{
		mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
		exit(0);
	}
	return (0);
}

void	draw_line(t_mlx_win *mlx_win, t_coords *point_a, t_coords *point_b)
{
	(void)point_a;
	(void)point_b;
	int	x;
	int	y;
	//mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, 100, 100, 0x08a394);
	//mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, 150, 150, 0xffffff);

	mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, point_a->x, point_a->y, 0x08a394);
	x = point_a->x;
	y = point_a->y;
	while (x < point_b->x)
	{
		y = ((point_b->y - point_a->y) / (point_b->x - point_a->x)) * (x - point_a->x) + point_a->y + 0.5;
		printf("y is %d, ", y);
		mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, x, y, 0xa37208);
		x++;
	}
	mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, point_b->x, point_b->y, 0xffffff);
}

void	open_mlx(int **map, size_t width, size_t length, char *file)
{
	void	*mlx_ptr;
	void	*window;
	t_mlx_win *mlx_win;
	t_coords	*point_a;
	t_coords	*point_b;

	(void)mlx_ptr;
	(void)window;
	(void)map;
	(void)width;
	(void)length;
	printf("width is %zu and lenth is %zu\n", width, length);

	mlx_ptr = handle_null(mlx_init());
	window = handle_null(mlx_new_window(mlx_ptr, 500, 500, file));
	mlx_win = (t_mlx_win *)malloc(sizeof(t_mlx_win));
	if (!mlx_win)
		handle_error();
	mlx_win->mlx_ptr = mlx_ptr;
	mlx_win->window = window;
	mlx_win->map = map;

	point_a = (t_coords *)malloc(sizeof(t_coords));
	if (!point_a)
		handle_error();
	point_b = (t_coords *)malloc(sizeof(t_coords));
	if (!point_b)
		handle_error();
	point_a->x = 100;
	point_a->y = 100;
	point_a->z = 0;
	point_b->x = 150;
	point_b->y = 110;
	point_b->z = 0;
	draw_line(mlx_win, point_a, point_b);
	mlx_key_hook(window, deal_key, (void *)mlx_win);
	mlx_loop(mlx_ptr);
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

	map_width = 0;
	map_len = get_map_size_y(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error();
	ret = get_next_line(fd, &line);
	j = 0;
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
	open_mlx(map, map_width, map_len, file);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		print_usage();
	parse_file(argv[1]);
	return (0);
}

/*

okayyeee alors.
comment storer les infos de la map??
(ah et why d3 ça marche qd mm ffs)

on sait pas avant de parser tout le file le nb de lignes, right?
et on sait pas au debut le nb de colonnes
donc l'array d'array d'ints ça marche pas
enfin on peut go first once, ensuite malloc, et re
mais c moche



*/