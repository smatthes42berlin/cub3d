#include "cub3d.h"

int	parse_whole_file(t_parse_state *parse_state)
{
	while (parse_state->cur_line)
	{
		identify_line(parse_state);
	}
	return (0);
}

int	identify_line(t_parse_state *parse_state)
{
	t_optn_parse	*check_optn;

	check_optn = is_optn(parse_state);
	if (is_newline(parse_state))
		return (handle_newline(parse_state));
	if (check_optn)
		return (handle_optn(parse_state, check_optn));
	if (is_map_start(parse_state) && !map_already_ended(parse_state))
		return (handle_map_start(parse_state));
	else
		return (handle_unknown(parse_state));
}
