/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:44:47 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/28 15:44:50 by mde-maul         ###   ########.fr       */
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

	*map = (int **)malloc(sizeof(int *) * size_y);
	if (!(*map))
		handle_error();
	i = 0;
	while (i < size_y)
	{
		(*map)[i] = (int *)malloc(sizeof(int) * size_x);
		if (i && !((*map)[i]))
		{
			free_map(*map, i - 1);
			handle_error();
		}
		i++;
	}
}
