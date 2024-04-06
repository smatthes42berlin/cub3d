#include "cub3d.h"

int	handle_map_start(t_parse_state *parse_state)
{
	printf("handling map start!\n");
	get_map_max_dim(parse_state);
	printf("width %d\n", parse_state->map_parse.max_width);
	printf("height %d\n", parse_state->map_parse.max_height);
	// go_to_next_line(parse_state);
	exit(123);
	return (0);
}

int	get_map_max_dim(t_parse_state *parse_state)
{
	t_list_d	*cur_line;

	cur_line = parse_state->cur_line;
	while (cur_line && ft_strcmp((char *)cur_line->content, "\n"))
	{
		parse_state->map_parse.max_height++;
		parse_state->map_parse.max_width = MAX((int)ft_strlen((char *)cur_line->content),
												parse_state->map_parse.max_width);
		cur_line = cur_line->next;
	}
	return (0);
}

// go until map end
// save height and width of needed array
// save strings in map array
// set map ended to true