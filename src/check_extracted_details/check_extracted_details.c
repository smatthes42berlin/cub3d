#include "cub3d.h"

int	check_extracted_details(t_parse_state *parse_state)
{
	check_map_validity(parse_state);
	check_option_tex(&(parse_state->texture_east));
	check_option_tex(&(parse_state->texture_west));
	check_option_tex(&(parse_state->texture_north));
	check_option_tex(&(parse_state->texture_south));
	check_option_col(&(parse_state->color_ceiling));
	check_option_col(&(parse_state->color_floor));
	return (0);
}
