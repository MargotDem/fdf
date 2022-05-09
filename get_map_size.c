/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:04:40 by mde-maul          #+#    #+#             */
/*   Updated: 2022/05/09 11:04:46 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_map_length(char *file)
{
	int		fd;
	char	*line;
	size_t	map_size_y;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error();
	map_size_y = 0;
	while (get_next_line(fd, &line))
	{
		map_size_y++;
		free(line);
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
	free(line);
	return (map_width);
	close(fd); // ???? mystere mysterieux
}

/*
ok so when closing the fd in getmapwidth. it segfautls.
what the actual fuckidy fuck is going onn
*/
