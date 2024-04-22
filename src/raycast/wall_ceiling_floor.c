#include "cub3d.h"

unsigned int	convert_rgb_to_hex(int *rgb)
{
	unsigned int	hex_color;

	hex_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (hex_color);
}

void	generate_3d_projection(t_main_data *data, t_ray *rays)
{
	int			i;
	float		perp_distance;
	float		distance_proj_plane;
	float		projected_wall_height;
	int			wall_strip_height;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	int			y;
	u_int32_t	texel_color;
	int			texture_offset_x;
	int			texture_offset_y;
	int			distance_from_top;

	i = 0;
	while (i < NUM_RAYS)
	{
		perp_distance = rays[i].distance * cos(rays[i].ray_angle
				- data->player.rotation_angle);
		distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / perp_distance)
			* distance_proj_plane;
		wall_strip_height = projected_wall_height;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom_pixel;
		// setting color of ceiling
		// unsigned ceiling_color = convert_rgb_to_hex(data->map.color_ceiling);
		y = 0;
		while (y < wall_top_pixel)
		{
			data->color_buffer[(WINDOW_WIDTH * y) + i] = 0xFF333333;
			// ceiling_color;
			y++;
		}
		///////////////////////////////////////
		////// rendering the walls ////////////
		///////////////////////////////////////
		/*// walls in coded texture
		y = wall_top_pixel;
		if (rays[i].was_hit_vertical)
			texture_offset_x = (int)rays[i].wall_hit_y % TILE_SIZE;
		else
			texture_offset_x = (int)rays[i].wall_hit_x % TILE_SIZE;
		while (y < wall_bottom_pixel)
		{
			distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT
					/ 2);
			texture_offset_y = distance_from_top * ((float)TEXTURE_HEIGHT
					/ wall_strip_height);
			texel_color = data->wall_texture[(TEXTURE_WIDTH * texture_offset_y)
				+ texture_offset_x];
			data->color_buffer[(WINDOW_WIDTH * y) + i] = texel_color;
			y++;
		}
		*/
		y = wall_top_pixel;
		if (rays[i].was_hit_vertical)
			texture_offset_x = (int)rays[i].wall_hit_y % TILE_SIZE;
		else
			texture_offset_x = (int)rays[i].wall_hit_x % TILE_SIZE;
		while (y < wall_bottom_pixel)
		{
			if (rays[i].hit_side == NORTH)
			{
				distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT
						/ 2);
				texture_offset_y = distance_from_top
					* ((float)data->textures.north.height / wall_strip_height);
				texel_color = data->textures.north.mem[(data->textures.north.width
						* texture_offset_y) + texture_offset_x];
				data->color_buffer[(WINDOW_WIDTH * y) + i] = texel_color;
			}
			else if (rays[i].hit_side == SOUTH)
			{
				distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT
						/ 2);
				texture_offset_y = distance_from_top
					* ((float)data->textures.south.height / wall_strip_height);
				texel_color = data->textures.south.mem[(data->textures.south.width
						* texture_offset_y) + texture_offset_x];
				data->color_buffer[(WINDOW_WIDTH * y) + i] = texel_color;
			}
			else if (rays[i].hit_side == EAST)
			{
				distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT
						/ 2);
				texture_offset_y = distance_from_top
					* ((float)data->textures.east.height / wall_strip_height);
				texel_color = data->textures.east.mem[(data->textures.east.width
						* texture_offset_y) + texture_offset_x];
				data->color_buffer[(WINDOW_WIDTH * y) + i] = texel_color;
			}
			else if (rays[i].hit_side == WEST)
			{
				distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT
						/ 2);
				texture_offset_y = distance_from_top
					* ((float)data->textures.west.height / wall_strip_height);
				texel_color = data->textures.west.mem[(data->textures.west.width
						* texture_offset_y) + texture_offset_x];
				data->color_buffer[(WINDOW_WIDTH * y) + i] = texel_color;
			}
			y++;
		}
		/* Walls in Four Colours
		y = wall_top_pixel;
		while (y < wall_bottom_pixel)
		{
			if (rays[i].hit_side == NORTH)
				data->color_buffer[(data->w.width * y) + i] = 0xFF0000; // Red
			else if (rays[i].hit_side == SOUTH)
				data->color_buffer[(data->w.width * y) + i] = 0x00FF00; // Green
			else if (rays[i].hit_side == EAST)
				data->color_buffer[(data->w.width * y) + i] = 0xFFFF00;
					// Yellow
			else if (rays[i].hit_side == WEST)
				data->color_buffer[(data->w.width * y) + i] = 0x0000FF; // Blue
			y++;
		}
		*/
		/* Wall in two colours
		y = wall_top_pixel;
		while (y < wall_bottom_pixel)
		{
			data->color_buffer[(WINDOW_WIDTH * y)
				+ i] = rays[i].was_hit_vertical ? 0xFFFFFFFF : 0xFFCCCCCC;
			y++;
		}
		*/
		// setting color of floor
		// unsigned floor_color = convert_rgb_to_hex(data->map.color_floor);
		y = wall_bottom_pixel;
		while (y < WINDOW_HEIGHT)
		{
			data->color_buffer[(WINDOW_WIDTH * y) + i] = 0xFF777777;
			// floor_color
			y++;
		}
		i++;
	}
}
