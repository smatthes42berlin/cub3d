#include "cub3d.h"

int	free_file_lbl(t_list_dc **file_lbl)
{
	d_lst_clear(file_lbl, free);
	return (0);
}

int	free_parse_state(t_parse_state *parse_state)
{
	if (parse_state)
	{
		free(parse_state->texture_east.line_in_map_file);
		free(parse_state->texture_north.line_in_map_file);
		free(parse_state->texture_south.line_in_map_file);
		free(parse_state->texture_west.line_in_map_file);
		free(parse_state->color_ceiling.line_in_map_file);
		free(parse_state->color_floor.line_in_map_file);
		free(parse_state->cur_line);
		free(parse_state->cur_line_trimmed);
		free_str_arr_null(parse_state->map_parse.org_rect);
		free_str_arr_null(parse_state->map_parse.reachable_rect);
		d_lst_clear(&(parse_state->file_lbl), free);
		ft_lstclear(&(parse_state->map_parse.queue), free);
		parse_state = NULL;
	}
	return (0);
}