#include "cub3d.h"

int	init_parse_state(t_parse_state *parse_state, t_main_data *main_data,
		t_list_dc *file_lbl)
{
	init_parse_state_gen(parse_state, main_data, file_lbl);
	init_parse_state_map(parse_state);
	init_parse_state_optns(parse_state);
	return (0);
}

int	init_parse_state_gen(t_parse_state *parse_state, t_main_data *main_data,
		t_list_dc *file_lbl)
{
	parse_state->main_data = main_data;
	parse_state->file_lbl = file_lbl;
	parse_state->cur_line = file_lbl;
	parse_state->cur_line_trimmed = NULL;
	get_cur_line_trimmed(parse_state);
	parse_state->unknown_lines_found = false;
	parse_state->defs_after_map_found = false;
	parse_state->any_error = false;
	return (0);
}

int	init_parse_state_map(t_parse_state *parse_state)
{
	parse_state->map_parse.unknown_char = false;
	parse_state->map_parse.no_start_pos = false;
	parse_state->map_parse.multi_start_pos = false;
	parse_state->map_parse.not_closed = false;
	parse_state->map_parse.started = false;
	parse_state->map_parse.ended = false;
	parse_state->map_parse.over_size_limit = false;
	parse_state->map_parse.org_rect = NULL;
	parse_state->map_parse.queue = NULL;
	parse_state->map_parse.reachable_rect = NULL;
	parse_state->map_parse.max_height_org = 0;
	parse_state->map_parse.max_width_org = 0;
	parse_state->map_parse.max_width_reachable = 0;
	parse_state->map_parse.max_height_reachable = 0;
	parse_state->map_parse.start_orient = '\0';
	parse_state->map_parse.reachable_height_min = 0;
	parse_state->map_parse.reachable_height_max = 0;
	parse_state->map_parse.reachable_width_min = 0;
	parse_state->map_parse.reachable_width_max = 0;
	parse_state->map_parse.start_pos[0] = 0;
	parse_state->map_parse.start_pos[1] = 0;
	parse_state->map_parse.parse_state = parse_state;
	return (0);
}

int	init_parse_state_optns(t_parse_state *parse_state)
{
	init_optn(&(parse_state->texture_east), "EA ", OPTN_TEXTURE, parse_state);
	init_optn(&(parse_state->texture_north), "NO ", OPTN_TEXTURE, parse_state);
	init_optn(&(parse_state->texture_south), "SO ", OPTN_TEXTURE, parse_state);
	init_optn(&(parse_state->texture_west), "WE ", OPTN_TEXTURE, parse_state);
	init_optn(&(parse_state->color_ceiling), "C ", OPTN_COLOR, parse_state);
	init_optn(&(parse_state->color_floor), "F ", OPTN_COLOR, parse_state);
	return (0);
}

int	init_optn(t_optn_parse *optn, const char *name, enum e_optn_type type,
		t_parse_state *parse_state)
{
	optn->identifier = name;
	optn->type = type;
	optn->line_in_map_file = NULL;
	optn->multi_def = false;
	optn->wrong_format = false;
	optn->file_access = true;
	optn->rgb_out_of_range = false;
	optn->parse_state = parse_state;
	optn->color[0] = -1;
	optn->color[1] = -1;
	optn->color[2] = -1;
	return (0);
}
