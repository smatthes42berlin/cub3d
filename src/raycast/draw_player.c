/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:59:35 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/15 14:59:39 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_direction(t_main_data *data, int *addr)
{
	int	start_x;
	int	start_y;
	int	line_end_x;
	int	line_end_y;
	int	scaled_line_length;

	scaled_line_length = 30 * MINIMAP_SCALE_FACTOR;
	start_x = (data->player.x + data->player.size / 2) * MINIMAP_SCALE_FACTOR;
	start_y = (data->player.y + data->player.size / 2) * MINIMAP_SCALE_FACTOR;
	line_end_x = start_x + cos(data->player.rotation_angle)
		* scaled_line_length;
	line_end_y = start_y + sin(data->player.rotation_angle)
		* scaled_line_length;
	draw_line_on_image(addr, WINDOW_WIDTH, WINDOW_HEIGHT, start_x, start_y,
		line_end_x, line_end_y, 0xFFFF00);
}

void	draw_player(t_main_data *data, int *addr)
{
	int	y;
	int	x;
	int	scaled_x;
	int	scaled_y;
	int	pixel_index;
	int	scaled_size;

	y = 0;
	scaled_size = data->player.size * MINIMAP_SCALE_FACTOR;
	while (y < scaled_size)
	{
		x = 0;
		while (x < scaled_size)
		{
			scaled_x = data->player.x * MINIMAP_SCALE_FACTOR + x;
			scaled_y = data->player.y * MINIMAP_SCALE_FACTOR + y;
			if (scaled_x >= 0 && scaled_x < WINDOW_WIDTH && scaled_y >= 0
				&& scaled_y < WINDOW_HEIGHT)
			{
				pixel_index = scaled_y * WINDOW_WIDTH + scaled_x;
				addr[pixel_index] = data->player.color;
			}
			x++;
		}
		y++;
	}
}