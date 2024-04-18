#ifndef CUB3D_TYPEDEF_H
# define CUB3D_TYPEDEF_H

# define REM_EMPTY_LINES_MAP_FILE false
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define MAX_TILES 64
# define MAP_SIZE_LIMIT_FLOOD_FILL 1000000000
# define PI 3.1415926535
# define PI2 PI / 2
# define PI3 3 * PI / 2
// cannot be '?' or '-'
# define FLOOD_CHAR '_'

// 111111111111999
// 100000000001111
// 100000000000001
// 100111111111119
// 111199999999999

typedef struct s_map
{
	int							tiles[MAX_TILES];
	int							width;
	int							height;
	int size; // size of each tile
	//
	char						*texture_north;
	char						*texture_south;
	char						*texture_east;
	char						*texture_west;
	int							color_ceiling[3];
	int							color_floor[3];
	int							**map;
}								t_map;

typedef struct s_player
{
	int							x;
	int							y;
	int							size;
	int							color;
	float						angle;
	float						dx;
	float						dy;
}								t_player;

typedef struct s_window
{
	void						*mlx;
	void						*mlx_win;
	int							width;
	int							height;
}								t_window;

typedef struct s_main_data
{
	// t_map				map;
	int							argc;
	char						**argv;
	t_window					w;
	t_player					player;
	t_map						map;
	// player start_position
	// player cur_position
	// player orientation
	//
}								t_main_data;

/* map parsing */

typedef struct s_parse_state	t_parse_state;

enum							e_optn_type
{
	OPTN_TEXTURE,
	OPTN_COLOR
};

typedef struct s_optn_parse
{
	char						*line_in_map_file;
	const char					*identifier;
	bool						multi_def;
	bool						wrong_format;
	bool						file_access;
	bool						rgb_out_of_range;
	int							color[3];
	enum e_optn_type			type;
	t_parse_state				*parse_state;
}								t_optn_parse;

typedef struct s_map_parse
{
	char						**org_rect;
	char						**reachable_rect;
	int							reachable_height_min;
	int							reachable_height_max;
	int							reachable_width_min;
	int							reachable_width_max;
	bool						multi_start_pos;
	bool						unknown_char;
	bool						no_start_pos;
	bool						over_size_limit;
	int							start_pos[2];
	char						start_orient;
	bool						more_than_one_start_pos;
	bool						not_closed;
	bool						started;
	bool						ended;
	int							max_height_org;
	int							max_width_org;
	int							max_height_reachable;
	int							max_width_reachable;
	t_list						*queue;
	t_parse_state				*parse_state;
}								t_map_parse;

typedef struct s_parse_state
{
	t_main_data					*main_data;
	t_list_dc					*file_lbl;
	t_list_dc					*cur_line;
	char						*cur_line_trimmed;
	bool						unknown_lines_found;
	bool						defs_after_map_found;
	t_optn_parse				texture_north;
	t_optn_parse				texture_south;
	t_optn_parse				texture_east;
	t_optn_parse				texture_west;
	t_optn_parse				color_ceiling;
	t_optn_parse				color_floor;
	t_map_parse					map_parse;
}								t_parse_state;

enum							e_failed_func
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
	int							err_code;
	enum e_failed_func			failed_func;
	char						*add_info;
}								t_error_ms;

#endif
