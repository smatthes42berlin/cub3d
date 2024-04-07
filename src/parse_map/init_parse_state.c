#include "cub3d.h"

int	init_parse_state(t_parse_state *parse_state, t_main_data *main_data,
		t_list_d *file_lbl)
{
	init_parse_state_gen(parse_state, main_data, file_lbl);
	init_parse_state_map(parse_state);
	init_parse_state_optns(parse_state);
	return (0);
}

int	init_parse_state_gen(t_parse_state *parse_state, t_main_data *main_data,
		t_list_d *file_lbl)
{
	parse_state->main_data = main_data;
	parse_state->file_lbl = file_lbl;
	parse_state->cur_line = file_lbl;
	parse_state->cur_line_trimmed = NULL;
	parse_state->map_file_valid = true;
	get_cur_line_trimmed(parse_state);
	parse_state->unknown_lines_found = false;
	parse_state->defs_after_map_found = false;
	return (0);
}

int	init_parse_state_map(t_parse_state *parse_state)
{
	parse_state->map_parse.multi_start_pos = false;
	parse_state->map_parse.unknown_char = false;
	parse_state->map_parse.no_start_pos = false;
	parse_state->map_parse.not_closed = false;
	parse_state->map_parse.started = false;
	parse_state->map_parse.ended = false;
	parse_state->map_parse.org_map_rect = NULL;
	parse_state->map_parse.reachable_map_rect = NULL;
	parse_state->map_parse.max_height_org = 0;
	parse_state->map_parse.max_width_org = 0;
	parse_state->map_parse.max_width_reachable = 0;
	parse_state->map_parse.max_height_reachable = 0;
	return (0);
}

int	init_parse_state_optns(t_parse_state *parse_state)
{
	init_optn(&(parse_state->texture_east), "EA ", OPTN_TEXTURE);
	init_optn(&(parse_state->texture_north), "NO ", OPTN_TEXTURE);
	init_optn(&(parse_state->texture_south), "SO ", OPTN_TEXTURE);
	init_optn(&(parse_state->texture_west), "WE ", OPTN_TEXTURE);
	init_optn(&(parse_state->color_ceiling), "C ", OPTN_COLOR);
	init_optn(&(parse_state->color_floor), "F ", OPTN_COLOR);
	return (0);
}

int	init_optn(t_optn_parse *optn, const char *name, enum e_optn_type type)
{
	optn->identifier = name;
	optn->type = type;
	optn->line_in_map_file = NULL;
	optn->multi_def = false;
	optn->wrong_format = false;
	optn->file_access = true;
	optn->rgb_out_of_range = false;
	optn->color[0] = -1;
	optn->color[1] = -1;
	optn->color[2] = -1;
	return (0);
}
