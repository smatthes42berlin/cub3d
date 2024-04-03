#include "cub3d.h"

bool	is_no(t_parse_state *parse_state)
{
	return compare_line(parse_state, "NO ");
}
bool	is_so(t_parse_state *parse_state)
{
	return compare_line(parse_state, "SO ");
}
bool	is_we(t_parse_state *parse_state)
{
	return compare_line(parse_state, "WE ");
}
bool	is_ea(t_parse_state *parse_state)
{
	return compare_line(parse_state, "EA ");
}
