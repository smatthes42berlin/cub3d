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

void	draw_tile(int *addr, int tile_x, int tile_y, int tile_color)
{
	int	scaled_tile_size;
	int	y;
	int	x;
	int	pixel_index;

	scaled_tile_size = (int)(TILE_SIZE * MINIMAP_SCALE_FACTOR);
	y = 0;
	while (y < scaled_tile_size)
	{
		x = 0;
		while (x < scaled_tile_size)
		{
			pixel_index = ((tile_y + y) * WINDOW_WIDTH + (tile_x + x));
			if (pixel_index < WINDOW_WIDTH * WINDOW_HEIGHT)
			{
				addr[pixel_index] = tile_color;
			}
			x++;
		}
		y++;
	}
}

void	draw_map(t_main_data *data, int *addr)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;
	int	tile_color;

	i = 0;
	while (i < data->map.rows)
	{
		j = 0;
		while (j < data->map.cols)
		{
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			if (data->map.map[i][j] == '1')
				tile_color = 0xFFFFFF;
			else
				tile_color = 0x000000;
			draw_tile(addr, tile_x * MINIMAP_SCALE_FACTOR, tile_y
				* MINIMAP_SCALE_FACTOR, tile_color);
			j++;
		}
		i++;
	}
}

void	draw_rays(t_main_data *data, int *addr, t_ray *rays)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line_on_image(addr, WINDOW_WIDTH, WINDOW_HEIGHT, data->player.x
			* MINIMAP_SCALE_FACTOR, data->player.y * MINIMAP_SCALE_FACTOR,
			rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR, rays[i].wall_hit_y
			* MINIMAP_SCALE_FACTOR, 0xFF0000);
		i++;
	}
}


/*
void draw_tile(int *addr, int tile_x, int tile_y, int tile_color)
{
    int scaled_tile_size = (int)(TILE_SIZE * MINIMAP_SCALE_FACTOR);
    for (int y = 0; y < scaled_tile_size; y++) {
        for (int x = 0; x < scaled_tile_size; x++) {
            int px = tile_x + x + MINIMAP_X_OFFSET;
            int py = tile_y + y + MINIMAP_Y_OFFSET;
            if (px >= MINIMAP_X_OFFSET && px < MINIMAP_X_OFFSET + MINIMAP_WIDTH &&
                py >= MINIMAP_Y_OFFSET && py < MINIMAP_Y_OFFSET + MINIMAP_HEIGHT) {
                int pixel_index = py * WINDOW_WIDTH + px;
                if (pixel_index < WINDOW_WIDTH * WINDOW_HEIGHT) { // Check to prevent buffer overflow
                    addr[pixel_index] = tile_color;
                }
            }
        }
    }
}

void draw_map(t_main_data *data, int *addr) {
    int viewport_size = VIEWPORT_SIZE;  // Define how many tiles around the player to show
    int player_tile_x = data->player.x / TILE_SIZE;  // Player's tile X
    int player_tile_y = data->player.y / TILE_SIZE;  // Player's tile Y

    // Calculate start and end columns and rows to draw based on the player's position
    int start_col = MAX(0, player_tile_x - viewport_size / 2);
    int start_row = MAX(0, player_tile_y - viewport_size / 2);
    int end_col = start_col + viewport_size;
    int end_row = start_row + viewport_size;

    // Adjust the viewport to stay within the map bounds and to not move too far when near edges
    if (end_col > data->map.cols) {
        start_col = data->map.cols - viewport_size;
        end_col = data->map.cols;
    }
    if (end_row > data->map.rows) {
        start_row = data->map.rows - viewport_size;
        end_row = data->map.rows;
    }

    // Ensure start_col and start_row are not negative after adjustment
    start_col = MAX(0, start_col);
    start_row = MAX(0, start_row);

    // Fill the background of the minimap with a neutral color
    for (int y = 0; y < MINIMAP_HEIGHT; y++) {
        for (int x = 0; x < MINIMAP_WIDTH; x++) {
            int pixel_index = y * WINDOW_WIDTH + x;
            if (pixel_index < WINDOW_WIDTH * WINDOW_HEIGHT) {
                addr[pixel_index] = 0xAAAAAA; // Grey color for out-of-bounds area
            }
        }
    }

    // Draw the map tiles within the calculated boundaries
    for (int i = start_row; i < end_row; i++) {
        for (int j = start_col; j < end_col; j++) {
            int tile_x = (j - start_col) * TILE_SIZE * MINIMAP_SCALE_FACTOR;
            int tile_y = (i - start_row) * TILE_SIZE * MINIMAP_SCALE_FACTOR;
            int tile_color = data->map.map[i][j] == '1' ? 0xFFFFFF : 0x000000;
            draw_tile(addr, tile_x, tile_y, tile_color);
        }
    }
}



*/

