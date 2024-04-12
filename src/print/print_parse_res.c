#include "cub3d.h"

int	print_parse_res(t_parse_state *parse_state)
{
	printf("\n***********Result of Parsing map file:********\n");
	print_gen_parse_res(parse_state);
	print_map_parse_res(parse_state);
	// print_optn_parse_res(&(parse_state->texture_south));
	// print_optn_parse_res(&(parse_state->texture_north));
	// print_optn_parse_res(&(parse_state->texture_east));
	// print_optn_parse_res(&(parse_state->texture_west));
	// print_optn_parse_res(&(parse_state->color_ceiling));
	// print_optn_parse_res(&(parse_state->color_floor));
	printf("\n***********                           ********\n\n");
	return (0);
}

int	print_optn_parse_res(t_optn_parse *optn)
{
	print_caption("Option");
	printf("Name: %s\n", optn->identifier);
	printf("line_in_map_file: %s\n", optn->line_in_map_file);
	print_res("multi_def", optn->multi_def);
	print_res("wrong_format", optn->wrong_format);
	print_res("file_access", optn->file_access);
	print_res("rgb_out_of_range", optn->rgb_out_of_range);
	printf("r: %d\n", (optn->color)[0]);
	printf("g: %d\n", (optn->color)[1]);
	printf("b: %d\n", (optn->color)[2]);
	return (0);
}

int	print_map_parse_res(t_parse_state *parse_state)
{
	print_caption("map parsing");
	print_res("multi_start_pos", parse_state->map_parse.multi_start_pos);
	print_res("unknown_char", parse_state->map_parse.unknown_char);
	print_res("no_start_pos", parse_state->map_parse.no_start_pos);
	print_res("not_closed", parse_state->map_parse.not_closed);
	print_res("not_found", !parse_state->map_parse.org_rect);
	print_caption("map org");
	printf("start height %d\n", (parse_state->map_parse.start_pos)[0]);
	printf("start width %d\n", (parse_state->map_parse.start_pos)[1]);
	printf("reachable height min %d\n", parse_state->map_parse.reachable_height_min);
	printf("reachable height max %d\n", parse_state->map_parse.reachable_height_max);
	printf("reachable width min %d\n", parse_state->map_parse.reachable_width_min);
	printf("reachable width max %d\n", parse_state->map_parse.reachable_width_max);
	print_map(parse_state->map_parse.org_rect,
				parse_state->map_parse.max_width_org,
				parse_state->map_parse.max_height_org);
	print_caption("map reachable");
	print_map(parse_state->map_parse.reachable_rect,
				parse_state->map_parse.max_width_reachable,
				parse_state->map_parse.max_height_reachable);
	return (0);
}

int	print_gen_parse_res(t_parse_state *parse_state)
{
	print_caption("general Parsing");
	print_res("unknown_lines_found", parse_state->unknown_lines_found);
	print_res("defs_after_map_found", parse_state->defs_after_map_found);
	return (0);
}
