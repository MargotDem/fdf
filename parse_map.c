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

size_t	get_map_length(char *file)
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

size_t	get_map_width(char *file)
{
	size_t		map_width;
	char		**data_ar;
	char		*line;
	int			ret;
	int			fd;

	map_width = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error();
	ret = get_next_line(fd, &line);
	data_ar = ft_strsplit(line, ' ');
	while (data_ar[map_width])
		map_width++;
	ft_free_str_array(data_ar, map_width);
	free(data_ar);
	return (map_width);
	close(fd);
}

void	parse_line(size_t *int_ar, int **map, int *highest, char **data_ar)
{
	size_t		i;

	i = 0;
	while (i < int_ar[1] && data_ar[i])
	{
		map[int_ar[0]][i] = ft_atoi(data_ar[i]);
		if (ft_atoi(data_ar[i]) > *highest)
			*highest = ft_atoi(data_ar[i]);
		i++;
	}
	if (i < int_ar[1])
		handle_error();
}

void	parse_lines(char *file, size_t map_width, int **map, int *highest)
{
	char		**data_ar;
	size_t		line_width;
	size_t		j;
	int			ret;
	int			fd;
	char		*line;
	size_t		int_ar[2];

	j = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error();
	ret = get_next_line(fd, &line);
	while (ret)
	{
		data_ar = ft_strsplit(line, ' ');
		line_width = 0;
		while (data_ar[line_width])
			line_width++;
		int_ar[0] = j;
		int_ar[1] = map_width;
		parse_line(int_ar, map, highest, data_ar);
		ret = get_next_line(fd, &line);
		j++;
		ft_free_str_array(data_ar, line_width);
		free(data_ar);
	}
	close(fd);
}

void	parse_map(char *file)
{
	size_t		map_width;
	size_t		map_length;
	int			**map;
	int			highest;
	t_mlx_win	*mlx_win;

	map_length = get_map_length(file);
	map_width = get_map_width(file);
	malloc_map(&map, map_width, map_length);
	highest = 0;
	parse_lines(file, map_width, map, &highest);
	mlx_win = create_mlx_win_struct(map, map_width, map_length, highest);
	open_mlx(mlx_win, file);
	free_map(map, map_length);
	free(mlx_win->base_point);
	free(mlx_win);
}
