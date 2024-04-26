#ifndef CUB3D_TYPEDEF_H
# define CUB3D_TYPEDEF_H

/* parser Macros */

# define REM_EMPTY_LINES_MAP_FILE false
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define MIN(a, b) ((a) > (b) ? (a) : (b))
# define MAP_SIZE_LIMIT_FLOOD_FILL 1000000000
# define MAX_REC_DEPTH 35000
// cannot be '?' or '-'
# define FLOOD_CHAR '_'
# define ERR_MSG "Error\n"
# define PRINT_DEBUG true
# define MAP_DIAG_CHECK false

# define FALSE 0
# define TRUE 1

# define PI 3.1415926535
# define TWO_PI 6.28318530

# define TILE_SIZE 64
# define TEXTURE_WIDTH TILE_SIZE
# define TEXTURE_HEIGHT TILE_SIZE

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 800

# define FOV_ANGLE (60 * (PI / 180))

# define NUM_RAYS (WINDOW_WIDTH)
//# define MINIMAP_SCALE_FACTOR 0.2

# define MINIMAP_SCALE_FACTOR 0.2

# define ROTATION_MOVEMENT 0.1
# define STRAIGHT_MOVEMENT 10

// extern int		map[MAP_NUM_ROWS][MAP_NUM_COLS];

# define REM_EMPTY_LINES_MAP_FILE false

typedef struct s_parse_state	t_parse_state;

typedef struct s_map
{
	int							cols;
	int							rows;
	int							size;
	// char						*texture_north;
	// char						*texture_south;
	// char						*texture_east;
	// char						*texture_west;
	int							color_ceiling[3];
	int							color_floor[3];
	char						**map;
}								t_map;

typedef enum e_wall_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall_side;

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
	t_wall_side					hit_side;
}							t_ray;

typedef struct s_raycast
{
	int is_ray_facing_down;
	int is_ray_facing_up;
	int is_ray_facing_right;
	int is_ray_facing_left;
	float xintercept;
	float yintercept;
	float xstep;
	float ystep;
	int found_horz_wall_hit;
	int found_vert_wall_hit;
	float horz_wall_hit_x;
	float horz_wall_hit_y;
	float vert_wall_hit_x;
	float vert_wall_hit_y;
	float next_horz_touch_x;
	float next_horz_touch_y;
	float next_vert_touch_x;
	float next_vert_touch_y;
	int horz_wall_content;
	int vert_wall_content;
	float ray_angle;
}	t_raycast;

typedef struct s_line
{
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		color;
}	t_line;

typedef struct s_draw_line
{
    int x;
	int y;
    int step_x;
	int step_y;
    int error;
	int error2;
    int delta_x;
	int delta_y;
} t_draw_line;

typedef struct s_draw_player
{
	int	y;
	int	x;
	int	scaled_x;
	int	scaled_y;
	int	pixel_index;
	int	scaled_size;
}	t_draw_player;

typedef struct s_tex
{
	char						*path;
	int							height;
	int							width;
	int							endian;
	int							line_size;
	int							bits_per_pixel;
	u_int32_t					*mem;
}								t_tex;

typedef struct s_render_wall
{
	t_tex		*tex;
	int			texture_offset_x;
	int			distance_from_top;
	int			texture_offset_y;
	u_int32_t	texel_color;

} t_render_wall;


typedef struct s_window
{
	void						*mlx;
	void						*mlx_win;
	int							width;
	int							height;
	float						scale_factor;
}								t_window;

typedef struct s_wall
{
	float		perp_distance;
	float		distance_proj_plane;
	float		projected_wall_height;
	int			wall_strip_height;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	int			y;
	u_int32_t	texel_color;
	int			texture_offset_x;
	int			texture_offset_y;
	int			distance_from_top;
}	t_wall;

typedef struct s_tex_all
{
	t_tex						north;
	t_tex						south;
	t_tex						east;
	t_tex						west;
	t_tex						*all[4];
}								t_tex_all;

typedef struct s_main_data
{
	int							argc;
	char						**argv;
	t_window					w;
	t_player					player;
	t_map						map;
	u_int32_t					*color_buffer;
	//u_int32_t					*wall_texture[4];
	t_tex_all 					textures;

	t_parse_state				*parse_state;
	// player start_pos_oition
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
	bool						multi_start_pos_o;
	bool						unknown_char;
	bool						no_start_pos_o;
	bool						over_size_limit;
	int							start_pos_o[2];
	int							start_pos_r[2];
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
