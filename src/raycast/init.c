#include "cub3d.h"

void	init_map(t_main_data *data)
{
	data->textures.north.path = 
		data->parse_state->texture_north.line_in_map_file;
	data->textures.south.path = 
		data->parse_state->texture_south.line_in_map_file;
	data->textures.east.path = data->parse_state->texture_east.line_in_map_file;
	data->textures.west.path = data->parse_state->texture_west.line_in_map_file;
	data->textures.all[0] = &(data->textures.north);
	data->textures.all[1] = &(data->textures.south);
	data->textures.all[2] = &(data->textures.east);
	data->textures.all[3] = &(data->textures.west);
	data->map.rows = data->parse_state->map_parse.max_height_reachable;
	data->map.cols = data->parse_state->map_parse.max_width_reachable;
	data->map.color_ceiling[0] = (data->parse_state->color_ceiling.color)[0];
	data->map.color_ceiling[1] = (data->parse_state->color_ceiling.color)[1];
	data->map.color_ceiling[2] = (data->parse_state->color_ceiling.color)[2];
	data->map.color_floor[0] = (data->parse_state->color_floor.color)[0];
	data->map.color_floor[1] = (data->parse_state->color_floor.color)[1];
	data->map.color_floor[2] = (data->parse_state->color_floor.color)[2];
	data->map.map = data->parse_state->map_parse.reachable_rect;
	data->parse_state->map_parse.reachable_rect = NULL;
	data->parse_state->texture_north.line_in_map_file = NULL;
	data->parse_state->texture_south.line_in_map_file = NULL;
	data->parse_state->texture_east.line_in_map_file = NULL;
	data->parse_state->texture_west.line_in_map_file = NULL;
}

void	init_player(t_main_data *data)
{
	data->player.x = data->parse_state->map_parse.start_pos_r[1] * TILE_SIZE
		+ (TILE_SIZE / 2);
	data->player.y = data->parse_state->map_parse.start_pos_r[0] * TILE_SIZE
		+ (TILE_SIZE / 2);
	data->player.size = 1;
	data->player.color = 0xFFFF00;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.rotation_angle = data->parse_state->map_parse.rotation_angle;
	data->player.walk_speed = 100;
	data->player.turn_speed = 45 * (PI / 180);
}

void	create_wall_texture(t_main_data *data)
{
	void	*img_ptr;
	t_tex	*tmp;
	int		i;

	i = 0;
	while (i < 4)
	{
		tmp = data->textures.all[i];
		img_ptr = read_file_to_image(data, tmp->path, &(tmp->width),
				&(tmp->height));
		if (!img_ptr)
		{
			ft_printf_fd(2, "Failed to load texture: %s\n", tmp->path);
			destroy_window(data);
			exit(1);
		}
		tmp->img_ptr = img_ptr;
		tmp->mem = (u_int32_t *)mlx_get_data_addr(img_ptr,
				&(tmp->bits_per_pixel), &(tmp->line_size), &(tmp->endian));
		i++;
	}
}

// if (str_ends_on(path, ".png"))
// 	return (mlx_png_file_to_image(data->w.mlx, path, width, height));

void	*read_file_to_image(t_main_data *data, char *path, int *width,
		int *height)
{
	if (str_ends_on(path, ".xpm"))
	{
		return (mlx_xpm_file_to_image(data->w.mlx, path, width, height));
	}
	return (NULL);
}

int	initialize_window(t_main_data *data)
{
	data->w.height = data->map.rows * TILE_SIZE;
	data->w.width = data->map.cols * TILE_SIZE;
	data->w.mlx = mlx_init();
	if (data->w.mlx == NULL)
		return (FALSE);
	data->w.mlx_win = mlx_new_window(data->w.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3d");
	if (data->w.mlx_win == NULL)
		return (FALSE);
	data->color_buffer = (u_int32_t *)malloc(sizeof(u_int32_t) * WINDOW_WIDTH
			* WINDOW_HEIGHT);
	if (!data->color_buffer)
		return (FALSE);
	return (TRUE);
}
