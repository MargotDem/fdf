/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:31:45 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:31:47 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(int **map, size_t size)
{
	size_t		j;

	j = 0;
	while (j < size)
	{
		free(map[j]);
		j++;
	}
	free(map);
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
			free_map(*map, i - 1);
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

size_t	get_map_size_y(char *file)
{
	int		ret;
	int		fd;
	char	*line;
	size_t	map_size_y;

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

void	parse_map(char *file)
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
	t_mlx_win	*mlx_win;

	map_width = 0;
	map_len = get_map_size_y(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error();
	ret = get_next_line(fd, &line);
	j = 0;
	highest = 0;
	data_ar = ft_strsplit(line, ' ');
	while (data_ar[map_width])
		map_width++;
	//free(data_ar);
	malloc_map(&map, map_width, map_len);
	while (ret)
	{
		i = 0;
		data_ar = ft_strsplit(line, ' ');
		while (i < map_width && data_ar[i])
		{
			map[j][i] = ft_atoi(data_ar[i]);
			if (ft_atoi(data_ar[i]) > (int)highest)
				highest = ft_atoi(data_ar[i]);
			i++;
		}
		if (i < map_width)
			handle_error();
		ret = get_next_line(fd, &line);
		j++;
		//free(data_ar);
	}
	close(fd);
	//print_map(map, map_width, map_len);
	mlx_win = create_mlx_win_struct(map, map_width, map_len, highest);
	open_mlx(mlx_win, file);
	free_map(map, map_len);
	free(mlx_win->base_point);
	free(mlx_win);
}
