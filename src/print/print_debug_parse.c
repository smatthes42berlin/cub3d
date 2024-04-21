#include "cub3d.h"

int	print_debug_org_map(t_parse_state *parse_state)
{
	if (PRINT_DEBUG)
	{
		print_map_parsing(parse_state, 'o');
	}
	return (0);
}

int	print_debug_reach_map(t_parse_state *parse_state)
{
	if (PRINT_DEBUG)
	{
		print_map_parsing(parse_state, 'r');
	}
	return (0);
}

int	print_debug_parse_res(t_parse_state *parse_state)
{
	if (PRINT_DEBUG)
	{
		print_parse_res(parse_state);
	}
	return (0);
}