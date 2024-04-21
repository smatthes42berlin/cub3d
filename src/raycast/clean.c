/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:58:51 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/15 14:58:53 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_window(t_main_data *data)
{
	t_xvar	*xvar;

	int i = 0;
	if (data->w.mlx_win != NULL)
	{
		mlx_destroy_window(data->w.mlx, data->w.mlx_win);
		data->w.mlx_win = NULL;
	}
	if (data->w.mlx != NULL)
	{
		xvar = (t_xvar *)data->w.mlx;
		if (xvar && xvar->display)
		{
			XCloseDisplay(xvar->display);
		}
		free(data->w.mlx);
		data->w.mlx = NULL;
	}
	if (data->wall_texture)
	{
		while (i < 4)
		{
			free(data->wall_texture[i]);
			i++;
		}
		free(data->wall_texture);
	}
	if (data->color_buffer)
		free(data->color_buffer);
}

int	close_window(void *param)
{
	t_main_data	*data;

	data = (t_main_data *)param;
	destroy_window(data);
	exit(0);
	return (0);
}
