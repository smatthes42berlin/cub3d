/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:59:00 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/15 14:59:02 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_color_buffer(t_main_data *data, u_int32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->w.width)
	{
		y = 0;
		while (y < data->w.height)
		{
			data->color_buffer[(data->w.width * y) + x] = color;
			y++;
		}
		x++;
	}
}
