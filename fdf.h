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
# include <fcntl.h>
# include "math.h"
// delete
# include <stdio.h>

typedef struct s_coords {
	int	x;
	int	y;
	int	floor;
	int	color;
}	t_coords;

typedef struct s_mlx_win {
	void		*mlx_ptr;
	void		*window;
	int			**map;
	size_t		map_width;
	size_t		map_length;
	size_t		window_width;
	size_t		window_length;
	t_coords	*base_point;
	int			rotation_a;
	size_t		highest;
	size_t		z_offset;
	size_t		x_offset;
	size_t		y_offset;
	size_t		x_y_offset;
	size_t		y_x_offset;
	size_t		projection;

	int			segment;
	t_coords	*point_a;
	t_coords	*point_b;
	t_coords	*point_c;
	t_coords	*point_d;
	int	off_x;
	int	off_x_y;
	int	off_y;
	int	off_y_x;
}	t_mlx_win;

void		print_usage(void);
void		handle_error(void);
void		*handle_null(void *param);
void		parse_map(char *file);
t_mlx_win	*create_mlx_win_struct(int **map, size_t width, \
	size_t length, size_t highest);
void		open_mlx(t_mlx_win *mlx_win, char *file);
int			handle_key(int key, void *param);
void		draw_map(t_mlx_win *mlx_win);
void		draw_line(t_mlx_win *mlx_win, t_coords *point_a, \
	t_coords *point_b);
int			round_point(float x);
void		print_pixel(t_mlx_win *mlx_win, t_coords *point_a);
void		erase_map(t_mlx_win *mlx_win);

#endif
