#include "cub3d.h"

void draw_player_direction(t_main_data *data, int *addr)
{
    int scaled_line_length = 30 * MINIMAP_SCALE_FACTOR; // Apply scaling to line length as well

    // Calculate the middle point of the player, applying the scale factor uniformly
    int start_x = (data->player.x + data->player.size / 2) * MINIMAP_SCALE_FACTOR;
    int start_y = (data->player.y + data->player.size / 2) * MINIMAP_SCALE_FACTOR;

    // Calculate the end point of the line, applying the scale factor to the line length
    int line_end_x = start_x + cos(data->player.rotation_angle) * scaled_line_length;
    int line_end_y = start_y + sin(data->player.rotation_angle) * scaled_line_length;
    
    draw_line_on_image(addr, data->w.width, data->w.height, start_x, start_y, line_end_x, line_end_y, 0xFFFF00);
}


void draw_player(t_main_data *data, int *addr)
{
    int y = 0;
    int scaled_size = data->player.size * MINIMAP_SCALE_FACTOR; // Scale the size of the player
    while (y < scaled_size) // Use scaled size
    {
        int x = 0;
        while (x < scaled_size) // Use scaled size
        {
            // Calculate the scaled position of the player
            int scaled_x = data->player.x * MINIMAP_SCALE_FACTOR + x;
            int scaled_y = data->player.y * MINIMAP_SCALE_FACTOR + y;

            // Ensure we are within the window boundaries
            if (scaled_x >= 0 && scaled_x < data->w.width && scaled_y >= 0 && scaled_y < data->w.height)
            {
                int pixel_index = scaled_y * data->w.width + scaled_x;
                addr[pixel_index] = data->player.color;
            }
            x++;
        }
        y++;
    }
}