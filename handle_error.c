/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:10:20 by mde-maul          #+#    #+#             */
/*   Updated: 2022/04/10 18:10:22 by mde-maul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(void)
{
	write(2, "error\n", 6);
	exit(1);
}

void	print_usage(void)
{
	//write(1, "Usage : ./fdf <filename> [ case_size z_size ]", 34);
	write(1, "Usage : ./fdf <filename>\n", 25);
}