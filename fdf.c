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

void	malloc_map(size_t ***map, size_t size_x, size_t size_y)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	*map = (size_t **)malloc(size_y);
	if (!(*map))
		handle_error();
	while (j < size_y)
	{
		(*map)[j] = (size_t *)malloc(size_x);
		if (!((*map)[j]))
		{
			while (i < j - 1)
			{
				free((*map)[i]);
				i++;
			}
			handle_error();
		}
		j++;
	}
}

void	parse_file(char *file, size_t ***map)
{
	int			ret;
	int			fd;
	size_t		i;
	size_t		j;
	size_t		map_size_x;
	size_t		map_size_y;
	char		*line;
	char		**data_ar;

	map_size_x = 0;
	map_size_y = get_map_size_y(file);
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
		if (!map_size_x)
		{
			while (data_ar[i])
				i++;
			map_size_x = i;
			printf("so x size is '%zu' and y size is '%zu'\n", map_size_x, map_size_y);
			malloc_map(map, map_size_x, map_size_y);
			i = 0;
		}
		while (i < map_size_x && data_ar[i])
		{
			printf("'%s' ", data_ar[i]);
			printf("sooo %d \n", ft_atoi(data_ar[i]));
			//(*map)[j][i] = (size_t)ft_atoi(data_ar[i]);
			i++;
		}
		if (i < map_size_x)
			handle_error();
		printf("\n");
		ret = get_next_line(fd, &line);
		j++;
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*window;
	size_t	size_x;
	size_t	size_y;
	size_t	**map;

	if (argc != 2)
		print_usage();
	//printf("heyyyy\n");
	size_x = 100;
	size_y = 100;
	(void)mlx_ptr;
	(void)window;
	(void)argv;
	// mlx_ptr = mlx_init();
	// window = mlx_new_window(mlx_ptr, size_x, size_y, "Test");
	// mlx_loop(mlx_ptr);
	parse_file(argv[1], &map);
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