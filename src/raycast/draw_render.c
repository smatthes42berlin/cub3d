/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:59:49 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/15 14:59:51 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_main_data *data, int *addr, t_ray *rays)
{
	fill_color_buffer(data, 0xFF000000);
	generate_3d_projection(data, rays);
	memcpy(addr, data->color_buffer, data->w.width * data->w.height
		* sizeof(u_int32_t));
	// display mini-map
	draw_map(data, addr);
	draw_player(data, addr);
	draw_player_direction(data, addr);
	draw_rays(data, addr, rays);
}

int	draw(t_main_data *data)
{
	void			*frame;
	int				*addr;
	static t_ray	rays[NUM_RAYS];

	frame = mlx_new_image(data->w.mlx, data->w.width, data->w.height);
	addr = (int *)mlx_get_data_addr(frame, &(int){32}, &(int){data->w.width
			* 4}, &(int){0});
	cast_all_rays(data, rays);
	render(data, addr, rays);
	mlx_put_image_to_window(data->w.mlx, data->w.mlx_win, frame, 0, 0);
	mlx_destroy_image(data->w.mlx, frame);
	return (0);
}
