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

int		handle_key(int key, void *param)
{
	t_mlx_win *mlx_win;

	mlx_win = (t_mlx_win *)param;
	printf("key is %d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(mlx_win->mlx_ptr, mlx_win->window);
		exit(0);
	}
	if (key == 123) // <
	{
		//printf("key is %d\n", key);
	}
	if (key == 35) // p
	{
		printf("heyyy\n");
		erase_map(mlx_win);
		if (mlx_win->projection == 0)
		{
			mlx_win->projection = 1;
		}
		else if (mlx_win->projection == 1)
		{
			mlx_win->projection = 0;
		}
		draw_map(mlx_win);
		//printf("key is %d\n", key);
	}
	return (0);
}
