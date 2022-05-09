/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:54:34 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:54:36 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		round_point(float x)
{
	if ((int)(x * 10) % 10 >= 5)
		return ((int)x + 1);
	return ((int)x);
}

void	print_pixel(t_mlx_win *mlx_win, t_coords *point)
{
	mlx_pixel_put(mlx_win->mlx_ptr, mlx_win->window, point->x, point->y, \
		point->color);
}
