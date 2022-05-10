/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:51:28 by mde-maul          #+#    #+#             */
/*   Updated: 2022/05/10 11:51:30 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_x(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	x;

	x = (mlx_win->base_point->x + (mlx_win->x_offset * i)) + \
		(mlx_win->x_y_offset * j);
	return (x);
}

size_t	get_y_floor(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	y;

	y = mlx_win->base_point->y - (mlx_win->y_offset * i) + \
		(mlx_win->y_x_offset * j);
	return (y);
}

size_t	get_y(t_mlx_win *mlx_win, size_t i, size_t j)
{
	size_t	y;

	y = get_y_floor(mlx_win, i, j) - (mlx_win->map[j][i] * mlx_win->z_offset);
	return (y);
}
