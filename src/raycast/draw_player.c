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

/*
void draw_player(t_main_data *data, int *addr) {
    int viewport_size = VIEWPORT_SIZE;  // Define how many tiles around the player to show
    int player_tile_x = data->player.x / TILE_SIZE;  // Player's tile X
    int player_tile_y = data->player.y / TILE_SIZE;  // Player's tile Y
    int scaled_size = data->player.size * MINIMAP_SCALE_FACTOR;  // Player's representation size on the minimap

    // Calculate the player's position relative to the viewport
    int start_col = MAX(0, player_tile_x - viewport_size / 2);
    int start_row = MAX(0, player_tile_y - viewport_size / 2);
    if (start_col + viewport_size > data->map.cols) {
        start_col = data->map.cols - viewport_size;
    }
    if (start_row + viewport_size > data->map.rows) {
        start_row = data->map.rows - viewport_size;
    }

    // Calculate player's minimap coordinates
    int minimap_x = MINIMAP_X_OFFSET + (player_tile_x - start_col) * TILE_SIZE * MINIMAP_SCALE_FACTOR;
    int minimap_y = MINIMAP_Y_OFFSET + (player_tile_y - start_row) * TILE_SIZE * MINIMAP_SCALE_FACTOR;

    // Draw the player on the minimap
    for (int y = 0; y < scaled_size; y++) {
        for (int x = 0; x < scaled_size; x++) {
            int px = minimap_x + x - scaled_size / 2;  // Center the player's icon
            int py = minimap_y + y - scaled_size / 2;
            if (px >= MINIMAP_X_OFFSET && px < MINIMAP_X_OFFSET + MINIMAP_WIDTH &&
                py >= MINIMAP_Y_OFFSET && py < MINIMAP_Y_OFFSET + MINIMAP_HEIGHT) {
                int pixel_index = py * WINDOW_WIDTH + px;
                if (pixel_index >= 0 && pixel_index < WINDOW_WIDTH * WINDOW_HEIGHT) { // Check to prevent buffer overflow
                    addr[pixel_index] = data->player.color; // Set player's color
                }
            }
        }
    }
}
*/