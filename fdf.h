/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:08:04 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/10 18:08:06 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <stdarg.h>
# include <stdlib.h>
#include <fcntl.h>
// delete
# include <stdio.h>

typedef struct s_mlx_win {
	void	*mlx_ptr;
	void	*window;
	int		**map;
}	t_mlx_win;

typedef struct s_coords {
	int	x;
	int	y;
	int	z;
}	t_coords;

void	print_usage(void);
void	handle_error(void);
void	*handle_null(void *param);

#endif
