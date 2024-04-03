#ifndef CUB3D_TYPEDEF_H
# define CUB3D_TYPEDEF_H

typedef struct s_map
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_east;
	char	*texture_west;
	int		color_ceiling[3];
	int		color_floor[3];
	int		**map;
}			t_map;

// 111111111111999
// 100000000001111
// 100000000000001
// 100111111111119
// 111199999999999

typedef struct s_main_data
{
	t_map	map;
	int		argc;
	char	**argv;
	// player start_position
	// player cur_position
	// player orientation
	//
}			t_main_data;


enum		e_failed_func
{
	ERROR_OPEN,
	ERROR_CLOSE,
	ERROR_READ,
	ERROR_WRITE,
	ERROR_PRINTF,
	ERROR_MALLOC,
	ERROR_FREE,
	ERROR_PERROR,
	ERROR_STRERROR,
	ERROR_EXIT
};

typedef struct s_error_ms
{
	int					err_code;
	enum e_failed_func	failed_func;
	char				*add_info;
}						t_error_ms;




#endif
