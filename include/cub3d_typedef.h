#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

define  

typedef struct s_map
{
	char		*texture_north;
	char		*texture_south;
	char		*texture_east;
	char		*texture_west;
	int			color_ceiling[3];
	int			color_floor[3];
	int**		map;
}				t_map;




// 111111111111999
// 100000000001111
// 100000000000001
// 100111111111119
// 111199999999999

typedef struct s_main_data
{
	t_map		*map;
	// player start_position
	// player cur_position
	// player orientation
	// 
}				t_main_data;

#endif
