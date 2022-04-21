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

int		round_point(float x)
{
	if ((int)(x * 10) % 10 >= 5)
	{
		//printf("arrondissons. %f\n", x);
		return ((int)x + 1);
	}
	//printf("n'arrondissons pas. %f\n", x);
	return ((int)x);
}
