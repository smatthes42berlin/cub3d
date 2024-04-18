/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:00:44 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/18 15:16:35 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_has_wall_at(t_main_data *data, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS
		* TILE_SIZE)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (data->map.map[map_grid_index_y][map_grid_index_x] == '1');
}
