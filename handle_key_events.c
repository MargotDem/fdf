/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:39:23 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/21 14:39:24 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * 53 esc
 * 35 p
 * 3 f
 * 5 g
 */

void	escape(t_mlx_win *mlx_win)
{
	mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
	exit(0);
}

void	switch_projection(t_mlx_win *mlx_win)
{
	erase_map(mlx_win);
	if (mlx_win->projection == 0)
		mlx_win->projection = 1;
	else if (mlx_win->projection == 1)
		mlx_win->projection = 0;
	draw_map(mlx_win);
}

void	mirror_horizontal(t_mlx_win *mlx_win)
{
	int			tmp;
	size_t		i;
	size_t		j;

	erase_map(mlx_win);
	j = 0;
	while (j < mlx_win->map_length)
	{
		i = 0;
		while (i < mlx_win->map_width / 2)
		{
			tmp = mlx_win->map[j][i];
			mlx_win->map[j][i] = \
				mlx_win->map[j][mlx_win->map_width - i - 1];
			mlx_win->map[j][mlx_win->map_width - i - 1] = tmp;
			i++;
		}
		j++;
	}
	draw_map(mlx_win);
}

void	mirror_vertical(t_mlx_win *mlx_win)
{
	size_t		j;
	int			*tmp;

	erase_map(mlx_win);
	j = 0;
	while (j < mlx_win->map_length / 2)
	{
		tmp = mlx_win->map[j];
		mlx_win->map[j] = mlx_win->map[mlx_win->map_length - j - 1];
		mlx_win->map[mlx_win->map_length - j - 1] = tmp;
		j++;
	}
	draw_map(mlx_win);
}

int	handle_key(int key, void *param)
{
	t_mlx_win	*mlx_win;

	mlx_win = (t_mlx_win *)param;
	if (key == 53)
		escape(mlx_win);
	if (key == 35)
		switch_projection(mlx_win);
	if (key == 3)
		mirror_horizontal(mlx_win);
	if (key == 5)
		mirror_vertical(mlx_win);
	return (0);
}
