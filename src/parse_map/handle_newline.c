#include "cub3d.h"

int	handle_newline(t_parse_state *parse_state)
{
	go_to_next_line(parse_state);
	return (0);
}
// wenn map nicht reached, just skip
// wenn map bereits reached, set map auf end,
// wenn es nicht bereits geschehen ist
// wenn map bereits ended, just skip