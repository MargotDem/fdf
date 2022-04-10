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

int	main(void)
{
	void	*mlx_ptr;
	void	*window;
	size_t	size_x;
	size_t	size_y;

	printf("heyyyy\n");
	size_x = 100;
	size_y = 100;
	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, size_x, size_y, "Test");
	mlx_loop(mlx_ptr);
}
