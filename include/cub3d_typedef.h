#ifndef CUB3D_TYPEDEF_H
# define CUB3D_TYPEDEF_H

/* parser Macros */

# define REM_EMPTY_LINES_MAP_FILE false
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define MAP_SIZE_LIMIT_FLOOD_FILL 1000000000
# define MAX_REC_DEPTH 35000
// cannot be '?' or '-'
# define FLOOD_CHAR '_'
# define ERR_MSG "Error\n"
# define PRINT_DEBUG false
# define MAP_DIAG_CHECK false

# define FALSE 0
# define TRUE 1



# define PI 3.1415926535
# define TWO_PI 6.28318530

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 180))

# define NUM_RAYS (WINDOW_WIDTH)
# define MINIMAP_SCALE_FACTOR 0.2

# define ROTATION_MOVEMENT 0.1
# define STRAIGHT_MOVEMENT 10

extern int						map[MAP_NUM_ROWS][MAP_NUM_COLS];

# define REM_EMPTY_LINES_MAP_FILE false
// 111111111111999
// 100000000001111
// 100000000000001
// 100111111111119
// 111199999999999

typedef struct s_parse_state	t_parse_state;

typedef struct s_map
{
	int							width;
	int							height;
	int							size;
	char						*texture_north;
	char						*texture_south;
	char						*texture_east;
	char						*texture_west;
	int							color_ceiling[3];
	int							color_floor[3];
	char						**map;
}								t_map;

typedef enum
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}								wall_side_t;

typedef struct s_player
{
	float						x;
	float						y;
	float						size;
	float						color;
	int							turn_direction;
	int							walk_direction;
	float						rotation_angle;
	int							straight_movement;
	float						walk_speed;
	float						turn_speed;
	float						delta_x;
	float						delta_y;
}								t_player;

typedef struct s_ray
{
	float						ray_angle;
	float						wall_hit_x;
	float						wall_hit_y;
	float						distance;
	int							was_hit_vertical;
	int							is_ray_facing_up;
	int							is_ray_facing_down;
	int							is_ray_facing_left;
	int							is_ray_facing_right;
	int							wall_hit_content;
	wall_side_t					hit_side;
}								t_ray;

typedef struct s_window
{
	void						*mlx;
	void						*mlx_win;
	int							width;
	int							height;
	float						scale_factor;
}								t_window;

typedef struct s_main_data
{
	// t_map				map;
	int							argc;
	char						**argv;
	t_window					w;
	t_player					player;
	t_map						map;
	u_int32_t					*color_buffer;
	t_parse_state				*parse_state;
	// player start_position
	// player cur_position
	// player orientation
	//
}								t_main_data;

/* map parsing */

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
	float						rotation_angle;
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
	bool						any_error;
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
