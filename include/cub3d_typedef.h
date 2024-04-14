#ifndef CUB3D_TYPEDEF_H
# define CUB3D_TYPEDEF_H

#define FALSE 0
#define TRUE 1

# define PI 3.1415926535
# define TWO_PI 6.28318530

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

#define FOV_ANGLE (60 * (PI / 180))

#define NUM_RAYS WINDOW_WIDTH
#define MINIMAP_SCALE_FACTOR 1.0

#define STRAIGHT_MOVEMENT (10 * MINIMAP_SCALE_FACTOR)
#define ROTATION_MOVEMENT 0.1

//# define PI2 PI / 2
//# define PI3 3 * PI / 2
//# define DR 0.0174533
//# define NUM_RAYS 60
// # define FOV (60 * DR)

# define REM_EMPTY_LINES_MAP_FILE false
// 111111111111999
// 100000000001111
// 100000000000001
// 100111111111119
// 111199999999999

typedef struct s_map
{
	int					width;
	int					height;
	int size; // size of each tile
	//
	char				*texture_north;
	char				*texture_south;
	char				*texture_east;
	char				*texture_west;
	int					color_ceiling[3];
	int					color_floor[3];
	int					**map;
}						t_map;

typedef struct s_player
{
	float					x;
	float					y;
	float					size;
	float					color;
	int						turn_direction;
	int						walk_direction;
	float 					rotation_angle;
	float 					walk_speed;
	float                   turn_speed;
	float 					delta_x;
	float 					delta_y;
}						t_player;

typedef struct s_ray 
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	int was_hit_vertical;
	int is_ray_facing_up;
	int is_ray_facing_down;
	int is_ray_facing_left;
	int is_ray_facing_right;
	int wall_hit_content;
}	t_ray;

typedef struct s_window
{
	void				*mlx;
	void				*mlx_win;
	int					width;
	int					height;
}						t_window;

typedef struct s_main_data
{
	// t_map				map;
	int					argc;
	char				**argv;
	t_window			w;
	t_player			player;
	t_map				map;
	// player start_position
	// player cur_position
	// player orientation
	//
}						t_main_data;

typedef struct s_parse_state
{
	t_main_data			*main_data;
	t_list_d			*file_lbl;
	t_list_d			*cur_line;
	char				*texture_north;
	char				*texture_south;
	char				*texture_east;
	char				*texture_west;
	char				*color_ceiling;
	char				*color_floor;
	bool				multi_def_tex_no;
	bool				multi_def_tex_so;
	bool				multi_def_tex_ea;
	bool				multi_def_tex_we;
	bool				multi_def_col_cei;
	bool				multi_def_col_flo;
	bool				wrong_format_tex_no;
	bool				wrong_format_tex_so;
	bool				wrong_format_tex_ea;
	bool				wrong_format_tex_we;
	bool				unknown_lines_found;
	bool				defs_after_map_found;
	bool				wrong_format_ceiling;
	bool				wrong_format_floor;
	bool				no_access_to_tex_no;
	bool				no_access_to_tex_so;
	bool				no_access_to_tex_ea;
	bool				no_access_to_tex_we;
	bool				map_multi_start_pos;
	bool				map_unknown_char;
	bool				map_no_start_pos;
	bool				map_not_closed;
	bool				map_started;
	bool				map_ended;
}						t_parse_state;

enum					e_failed_func
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
