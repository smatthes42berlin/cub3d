/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:59:24 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/18 15:15:17 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_WIDTH 300  // Width of the minimap display in pixels
#define MINIMAP_HEIGHT 300 // Height of the minimap display in pixels

void	update_minimap_scale_factor(t_main_data *data)
{
	float	scale_width;
	float	scale_height;

	scale_width = (float)MINIMAP_WIDTH / (data->map.cols * TILE_SIZE);
	scale_height = (float)MINIMAP_HEIGHT / (data->map.rows * TILE_SIZE);
	data->w.scale_factor = fmin(scale_width, scale_height);
}

void	draw_tile(int *addr, int tile_x, int tile_y, int tile_color,
		float scale_factor, int base_x, int base_y)
{
	int	scaled_tile_size;
	int	px;
	int	py;
	int	pixel_index;

	scaled_tile_size = (int)(TILE_SIZE * scale_factor);
	for (int y = 0; y < scaled_tile_size; y++)
	{
		for (int x = 0; x < scaled_tile_size; x++)
		{
			px = base_x + tile_x + x;
			py = base_y + tile_y + y;
			if (px < WINDOW_WIDTH && py < WINDOW_HEIGHT)
			{
				pixel_index = py * WINDOW_WIDTH + px;
				addr[pixel_index] = tile_color;
			}
		}
	}
}

void	draw_map(t_main_data *data, int *addr)
{
	int	tile_x;
	int	tile_y;
	int	tile_color;

	int base_x = 0; // Center the minimap horizontally
	int base_y = 0; // Center the minimap vertically
	for (int i = 0; i < data->map.rows; i++)
	{
		for (int j = 0; j < data->map.cols; j++)
		{
			tile_x = j * TILE_SIZE * data->w.scale_factor;
			tile_y = i * TILE_SIZE * data->w.scale_factor;
			tile_color = data->map.map[i][j] == '1' ? 0xFFFFFF : 0x000000;
			draw_tile(addr, tile_x, tile_y, tile_color, data->w.scale_factor,
				base_x, base_y);
		}
	}
}

void	draw_rays(t_main_data *data, int *addr, t_ray *rays)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line_on_image(addr, WINDOW_WIDTH, WINDOW_HEIGHT, data->player.x
			* data->w.scale_factor, data->player.y * data->w.scale_factor,
			rays[i].wall_hit_x * data->w.scale_factor, rays[i].wall_hit_y
			* data->w.scale_factor, 0xFF0000);
		i++;
	}
}
