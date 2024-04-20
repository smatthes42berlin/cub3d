#include "cub3d.h"

int	check_parse_res_main(t_parse_state *parse_state)
{
	check_gen_errors(parse_state);
	check_map_errors(parse_state);
	check_option_errors(parse_state, &(parse_state->texture_east));
	check_option_errors(parse_state, &(parse_state->texture_west));
	check_option_errors(parse_state, &(parse_state->texture_north));
	check_option_errors(parse_state, &(parse_state->texture_south));
	check_option_errors(parse_state, &(parse_state->color_ceiling));
	check_option_errors(parse_state, &(parse_state->color_floor));
	if (parse_state->any_error)
	{
		free_parse_state(parse_state);
		exit(0);
	}
	return (0);
}

int	check_gen_errors(t_parse_state *parse_state)
{
	if (parse_state->defs_after_map_found)
		print_error_msg(parse_state, "definitions after map found", "general");
	if (parse_state->unknown_lines_found)
		print_error_msg(parse_state, "not identifiable lines found", "general");
	return (0);
}

int	check_map_errors(t_parse_state *parse_state)
{
	if (parse_state->map_parse.multi_start_pos)
		print_error_msg(parse_state, "multiple start pos", "map");
	if (parse_state->map_parse.unknown_char)
		print_error_msg(parse_state, "unknown char found", "map");
	if (parse_state->map_parse.no_start_pos)
		print_error_msg(parse_state, "no start pos", "map");
	if (parse_state->map_parse.over_size_limit)
		print_error_msg(parse_state, "map bigger than size limit", "map");
	if (parse_state->map_parse.not_closed)
		print_error_msg(parse_state, "map not closed", "map");
	if (!parse_state->map_parse.started)
		print_error_msg(parse_state, "no map found", "map");
	return (0);
}

int	check_option_errors(t_parse_state *parse_state, t_optn_parse *optn)
{
	if (optn->multi_def)
		print_error_msg(parse_state, "multiple definitions", optn->identifier);
	if (optn->wrong_format)
		print_error_msg(parse_state, "wrong format", optn->identifier);
	if (!optn->file_access)
		print_error_msg(parse_state, "file cannot be opened", optn->identifier);
	if (optn->rgb_out_of_range)
		print_error_msg(parse_state, "rgb col def out of range",
			optn->identifier);
	return (0);
}

int	print_error_msg(t_parse_state *parse_state, char *msg, const char *ident)
{
	if (!parse_state->any_error)
	{
		parse_state->any_error = true;
		printf("Error\n");
	}
	printf("%s: ", ident);
	printf("%s\n", msg);
	return (0);
}
