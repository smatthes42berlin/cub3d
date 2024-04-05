#include "cub3d.h"

bool	compare_line(t_parse_state *parse_state, const char *str)
{
	return (ft_strncmp(str, (char *)parse_state->cur_line->content, ft_strlen(str)) == 0);
}

bool	is_newline(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "\n"));
}

bool	is_ceil(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "C "));
}

bool	is_floor(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "F "));
}

bool	is_map_start(t_parse_state *parse_state)
{
	char	*content;
	int		i;

	i = 0;
	content = parse_state->cur_line->content;
	while (content[i])
	{
		if (ft_isspace(content[i]))
			i++;
	}
	return (false);
}

// any number of ws
// encounter either a 1, 0, W,E,S,N,
