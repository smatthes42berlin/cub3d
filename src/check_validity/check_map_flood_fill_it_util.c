#include "cub3d.h"

int	get_cur_point_queue(t_parse_state *parse_state, int cur_point[2])
{
	int	cur_height;
	int	cur_width;

	cur_height = ((int *)(parse_state->map_parse.queue->content))[0];
	cur_width = ((int *)(parse_state->map_parse.queue->content))[1];
	cur_point[0] = cur_height;
	cur_point[1] = cur_width;
	return (0);
}

int	add_point_to_queue(t_parse_state *parse_state, int height, int width)
{
	int		*point;
	t_list	*new_lst;
	// int		cur_point[2];

	// cur_point[0] = height;
	// cur_point[1] = width;
	// if (cur_point[0] + 1 > parse_state->map_parse.max_height_org
	// 	|| cur_point[0] < 0)
	// 	return (0);
	// if (cur_point[1] + 1 > parse_state->map_parse.max_width_org
	// 	|| cur_point[1] < 0)
	// 	return (0);
	// if (parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] == 'X'
	// 	|| parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] == '1')
	// 	return (0);
	// if (parse_state->map_parse.org_rect[height][width] == 'X')
	// 	return (0);
	point = malloc(sizeof(*point) * 2);
	if (!point)
		throw_error_sys_call_parse((t_error_ms){errno, ERROR_MALLOC,
				"Cannot allocate memory for flood fill point!"}, parse_state,
				true);
	point[0] = height;
	point[1] = width;
	new_lst = ft_lstnew(point);
	if (!new_lst)
	{
		free(point);
		throw_error_sys_call_parse((t_error_ms){errno, ERROR_MALLOC,
				"Cannot allocate memory for flood fill point!"}, parse_state,
				true);
	}
	ft_lstadd_back(&(parse_state->map_parse.queue), new_lst);
	return (0);
}

int	remove_point_from_queue(t_parse_state *parse_state)
{
	t_list	*old_lst;

	old_lst = parse_state->map_parse.queue;
	parse_state->map_parse.queue = old_lst->next;
	ft_lstdelone(old_lst, free);
	return (0);
}

int	add_surrounding_points_queue(t_parse_state *parse_state, int *cur_point)
{
	add_point_to_queue(parse_state, cur_point[0] + 1, cur_point[1]);
	add_point_to_queue(parse_state, cur_point[0] - 1, cur_point[1]);
	add_point_to_queue(parse_state, cur_point[0], cur_point[1] + 1);
	add_point_to_queue(parse_state, cur_point[0], cur_point[1] - 1);
	return (0);
}
