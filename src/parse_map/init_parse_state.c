#include "cub3d.h"


int	init_parse_state(t_parse_state *parse_state, t_main_data *main_data,
		t_list_d *file_lbl)
{
	init_parse_state_gen(parse_state, main_data, file_lbl);
	init_parse_state_map(parse_state);
	init_parse_state_tex(parse_state);
	init_parse_state_col(parse_state);
	return (0);
}

int	init_parse_state_gen(t_parse_state *parse_state, t_main_data *main_data,
		t_list_d *file_lbl)
{
	parse_state->main_data = main_data;
	parse_state->file_lbl = file_lbl;
	parse_state->cur_line = file_lbl;
	parse_state->unknown_lines_found = false;
	parse_state->defs_after_map_found = false;
	return (0);
}

int	init_parse_state_map(t_parse_state *parse_state)
{
	parse_state->map_multi_start_pos = false;
	parse_state->map_unknown_char = false;
	parse_state->map_no_start_pos = false;
	parse_state->map_not_closed = false;
	parse_state->map_started = false;
	parse_state->map_ended = false;
	return (0);
}

int	init_parse_state_tex(t_parse_state *parse_state)
{
	parse_state->texture_north = NULL;
	parse_state->texture_south = NULL;
	parse_state->texture_east = NULL;
	parse_state->texture_west = NULL;
	parse_state->multi_def_tex_no = false;
	parse_state->multi_def_tex_so = false;
	parse_state->multi_def_tex_ea = false;
	parse_state->multi_def_tex_we = false;
	parse_state->wrong_format_tex_no = false;
	parse_state->wrong_format_tex_so = false;
	parse_state->wrong_format_tex_ea = false;
	parse_state->wrong_format_tex_we = false;
	parse_state->no_access_to_tex_no = false;
	parse_state->no_access_to_tex_so = false;
	parse_state->no_access_to_tex_ea = false;
	parse_state->no_access_to_tex_we = false;
	return (0);
}

int	init_parse_state_col(t_parse_state *parse_state)
{
	parse_state->multi_def_col_cei = false;
	parse_state->multi_def_col_flo = false;
	parse_state->color_ceiling = NULL;
	parse_state->color_floor = NULL;
	parse_state->wrong_format_ceiling = false;
	parse_state->wrong_format_floor = false;
	return (0);
}
