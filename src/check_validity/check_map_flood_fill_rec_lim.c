#include "cub3d.h"

int	flood_fill_rec_lim(t_parse_state *parse_state)
{
	int	start_width;
	int	start_height;
	int	cur_point[2];

	start_height = parse_state->map_parse.start_pos[0];
	start_width = parse_state->map_parse.start_pos[1];
	parse_state->map_parse.reachable_width_min = start_width;
	parse_state->map_parse.reachable_width_max = start_width;
	parse_state->map_parse.reachable_height_min = start_height;
	parse_state->map_parse.reachable_height_max = start_height;
	parse_state->map_parse.org_rect[start_height][start_width] = '0';
	add_point_to_queue(parse_state, start_height, start_width);
	while (parse_state->map_parse.queue)
	{
		get_cur_point_queue(parse_state, cur_point);
		flood_check_rec_lim(parse_state, cur_point[0], cur_point[1], 0);
		remove_point_from_queue(parse_state);
	}
	return (0);
}

int	flood_check_rec_lim(t_parse_state *parse_state, int height, int width,
		int rec_depth)
{
	int	cur_point[2];

	cur_point[0] = height;
	cur_point[1] = width;
	// ft_printf("Stack depth: %d\n", rec_depth);
	rec_depth++;
	if (cur_point[0] + 1 > parse_state->map_parse.max_height_org
		|| cur_point[0] < 0)
		return (0);
	if (cur_point[1] + 1 > parse_state->map_parse.max_width_org
		|| cur_point[1] < 0)
		return (0);
	if (parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] == FLOOD_CHAR
		|| parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] == '1')
		return (0);
	if (parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] == '0')
	{
		parse_state->map_parse.org_rect[cur_point[0]][cur_point[1]] = FLOOD_CHAR;
		if (rec_depth < 35000)
		{
			flood_check_rec_lim(parse_state, cur_point[0] + 1, cur_point[1],
					rec_depth);
			flood_check_rec_lim(parse_state, cur_point[0] - 1, cur_point[1],
					rec_depth);
			flood_check_rec_lim(parse_state, cur_point[0], cur_point[1] + 1,
					rec_depth);
			flood_check_rec_lim(parse_state, cur_point[0], cur_point[1] - 1,
					rec_depth);
			// if (flood_check_rec_lim(parse_state, cur_point[0] + 1, cur_point[1],
			// 		rec_depth))
			// {
			// 	add_point_to_queue(parse_state, cur_point[0] - 1, cur_point[1]);
			// 	add_point_to_queue(parse_state, cur_point[0], cur_point[1] + 1);
			// 	add_point_to_queue(parse_state, cur_point[0], cur_point[1] - 1);
			// 	return (1);
			// }
			// if (flood_check_rec_lim(parse_state, cur_point[0] - 1, cur_point[1],
			// 		rec_depth))
			// {
			// 	add_point_to_queue(parse_state, cur_point[0], cur_point[1] + 1);
			// 	add_point_to_queue(parse_state, cur_point[0], cur_point[1] - 1);
			// 	return (1);
			// }
			// if (flood_check_rec_lim(parse_state, cur_point[0], cur_point[1] + 1,
			// 		rec_depth))
			// {
			// 	add_point_to_queue(parse_state, cur_point[0], cur_point[1] - 1);
			// 	return (1);
			// }
			// if (flood_check_rec_lim(parse_state, cur_point[0], cur_point[1] - 1,
			// 		rec_depth))
			// 	return (1);
		}
		else
		{
			add_surrounding_points_queue(parse_state, cur_point);
			return (1);
		}
	}
	check_map_not_closed(parse_state, cur_point[0], cur_point[1]);
	adjust_reachable_map(parse_state, cur_point[0], cur_point[1]);
	return (0);
}
