/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:48:13 by mde-maul          #+#    #+#             */
/*   Updated: 2022/05/10 11:48:17 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	erase_map(t_mlx_win *mlx_win)
{
	size_t	i;
	size_t	j;
	int		color;
	size_t	width;
	size_t	length;

	width = mlx_win->window_width;
	length = mlx_win->window_length;
	color = 0x000000;
	i = 0;
	while (i < length)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, j, i, color);
			j++;
		}
		i++;
	}
}
