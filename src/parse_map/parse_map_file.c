#include "cub3d.h"

int	parse_map_file(t_main_data *main_data, t_list_dc *file_lbl)
{
	t_parse_state	*parse_state;

	parse_state = main_data->parse_state;
	if (!file_lbl)
		throw_error_gen(1, "Empty map file provided!", true);
	init_parse_state(parse_state, main_data, file_lbl);
	parse_whole_file(parse_state);
	print_debug_org_map(parse_state);
	check_extracted_details(parse_state);
	print_debug_parse_res(parse_state);
	check_parse_res_main(parse_state);
	return (0);
}
