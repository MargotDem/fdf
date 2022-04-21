/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mlx_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:34:36 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:34:44 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx_win	*create_mlx_win_struct(int **map, size_t width, size_t length, \
	size_t highest)
{
	t_mlx_win	*mlx_win;

	mlx_win = (t_mlx_win *)malloc(sizeof(t_mlx_win));
	if (!mlx_win)
		handle_error();
	mlx_win->map = map;
	mlx_win->map_width = width;
	mlx_win->map_length = length;
	mlx_win->rotation_a = 20;
	mlx_win->projection = 0;
	mlx_win->highest = highest;
	return (mlx_win);
}
