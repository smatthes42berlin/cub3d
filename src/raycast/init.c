/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:00:06 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/18 16:12:20 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_main_data *data)
{
	data->player.x = data->parse_state->map_parse.start_pos[1] * TILE_SIZE
		+ (TILE_SIZE / 2);
	data->player.y = data->parse_state->map_parse.start_pos[0] * TILE_SIZE
		+ (TILE_SIZE / 2);
	// data->player.x = WINDOW_WIDTH / 2;
	// data->player.y = WINDOW_HEIGHT / 2;
	data->player.size = 1;
	data->player.color = 0xFFFF00;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	// data->player.rotation_angle = PI / 2; // Player view at the beginning
	data->player.rotation_angle = data->parse_state->map_parse.rotation_angle;
	data->player.walk_speed = 100;
	data->player.turn_speed = 45 * (PI / 180);
}

void	init_map(t_main_data *data)
{
	data->map.width = data->parse_state->map_parse.max_width_org;
	data->map.height = data->parse_state->map_parse.max_height_org;
	data->map.texture_north = data->parse_state->texture_north.line_in_map_file;
	data->map.texture_south = data->parse_state->texture_south.line_in_map_file;
	data->map.texture_east = data->parse_state->texture_east.line_in_map_file;
	data->map.texture_west = data->parse_state->texture_west.line_in_map_file;
	data->map.color_ceiling[0] = (data->parse_state->color_ceiling.color)[0];
	data->map.color_ceiling[1] = (data->parse_state->color_ceiling.color)[1];
	data->map.color_ceiling[2] = (data->parse_state->color_ceiling.color)[2];
	data->map.color_floor[0] = (data->parse_state->color_floor.color)[0];
	data->map.color_floor[1] = (data->parse_state->color_floor.color)[1];
	data->map.color_floor[2] = (data->parse_state->color_floor.color)[2];
	data->map.map = data->parse_state->map_parse.org_rect;
	data->parse_state->map_parse.org_rect = NULL;
	data->parse_state->texture_north.line_in_map_file = NULL;
	data->parse_state->texture_south.line_in_map_file = NULL;
	data->parse_state->texture_east.line_in_map_file = NULL;
	data->parse_state->texture_west.line_in_map_file = NULL;
}

void	setup(t_main_data *data)
{
	init_player(data);
	init_map(data);
	free_parse_state(data->parse_state);
	data->color_buffer = (u_int32_t *)malloc(sizeof(u_int32_t) * WINDOW_WIDTH
			* WINDOW_HEIGHT);
}

int	initialize_window(t_main_data *data)
{
	data->w.height = WINDOW_HEIGHT;
	data->w.width = WINDOW_WIDTH;
	data->w.mlx = mlx_init();
	if (data->w.mlx == NULL)
		return (FALSE);
	data->w.mlx_win = mlx_new_window(data->w.mlx, data->w.width, data->w.height,
			"Cub3d");
	if (data->w.mlx_win == NULL)
		return (FALSE);
	return (TRUE);
}

int	init(t_main_data *data)
{
	if (!initialize_window(data))
	{
		destroy_window(data);
		return (FALSE);
	}
	setup(data);
	mlx_hook(data->w.mlx_win, 2, 1L << 0, keys, data);
	mlx_hook(data->w.mlx_win, 17, 0, close_window, data);
	mlx_loop_hook(data->w.mlx, draw, data);
	mlx_loop(data->w.mlx);
	destroy_window(data);
	return (TRUE);
}
