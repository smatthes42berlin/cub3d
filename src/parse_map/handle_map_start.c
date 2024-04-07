#include "cub3d.h"

// parse textures
// parse colors
// check map validity
// only one start pos
// played cannot go outside or map or reach map spaces
// create flood filled map
// shrink map to playable size
//

int	handle_map_start(t_parse_state *parse_state)
{
	get_map_max_dim(parse_state);
	if (allocate_arr_char(&(parse_state->map_parse.org_map_rect), MAP_SPACE,
			parse_state->map_parse.max_height_org,
			parse_state->map_parse.max_width_org))
		throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
				"Cannot allocate array for oprg map!"}, true);
	copy_array_from_file(parse_state);
	parse_state->map_parse.ended = true;
	return (0);
}

int	copy_array_from_file(t_parse_state *parse_state)
{
	char	*cur_line;
	int		i;
	int		j;

	j = 0;
	if (parse_state->cur_line)
		cur_line = parse_state->cur_line->content;
	while (parse_state->cur_line && ft_strcmp(cur_line, "\n")
		&& !str_is_empty(cur_line))
	{
		i = 0;
		while (cur_line[i])
		{
			(parse_state->map_parse.org_map_rect)[j][i] = cur_line[i];
			i++;
		}
		go_to_next_line(parse_state);
		if (parse_state->cur_line)
			cur_line = parse_state->cur_line->content;
		j++;
	}
	return (0);
}

int	get_map_max_dim(t_parse_state *parse_state)
{
	t_list_d	*cur_line;

	cur_line = parse_state->cur_line;
	while (cur_line && ft_strcmp((char *)cur_line->content, "\n")
		&& !str_is_empty((char *)cur_line->content))
	{
		parse_state->map_parse.max_height_org++;
		parse_state->map_parse.max_width_org = MAX((int)ft_strlen((char *)cur_line->content),
													parse_state->map_parse.max_width_org);
		cur_line = cur_line->next;
	}
	return (0);
}
