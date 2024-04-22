#include "cub3d.h"

int	create_reachable_map(t_parse_state *parse_state)
{
	t_map_parse	*tmp;

	tmp = &(parse_state->map_parse);
	tmp->max_height_reachable = tmp->reachable_height_max + 2
		- tmp->reachable_height_min + 1;
	tmp->max_width_reachable = tmp->reachable_width_max + 2
		- tmp->reachable_width_min + 1;
	if (subarr_arr_str(tmp->org_rect,
			(t_subarr_arr_str){
			tmp->reachable_height_min - 1,
			tmp->reachable_height_max + 2,
			tmp->reachable_width_min - 1,
			tmp->reachable_width_max + 2},
		&(tmp->reachable_rect)))
		throw_error_sys_call_parse((t_error_ms){errno, ERROR_MALLOC,
			"Cannot copy reachable map array!"}, parse_state, true);
	tmp->start_pos_r[0] = tmp->start_pos_o[0] - tmp->reachable_height_min + 1;
	tmp->start_pos_r[1] = tmp->start_pos_o[1]
		- parse_state->map_parse.reachable_width_min + 1;
	printf("start pos r height %d\n", tmp->start_pos_r[0]);
	printf("start pos r width %d\n", tmp->start_pos_r[1]);
	return (0);
}
