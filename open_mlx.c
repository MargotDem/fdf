/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:38:06 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:38:08 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_window_dimensions(size_t *dimensions , size_t width, size_t length)
{
	(void)width;
	(void)length;
	(dimensions)[0] = 600;
	(dimensions)[1] = 600;
}

void	open_mlx(t_mlx_win *mlx_win, char *file)
{
	void	*mlx_ptr;
	void	*window;
	size_t	dimensions[2];

	mlx_ptr = handle_null(mlx_init());

	get_window_dimensions(dimensions, mlx_win->map_width, mlx_win->map_length);
	window = handle_null(mlx_new_window(mlx_ptr, dimensions[0], dimensions[1], file));
	mlx_win->mlx_ptr = mlx_ptr;
	mlx_win->window = window;
	mlx_win->window_width = dimensions[0];
	mlx_win->window_length = dimensions[1];
	draw_map(mlx_win);
	mlx_key_hook(window, handle_key, (void *)mlx_win);
	mlx_loop(mlx_ptr);
}
