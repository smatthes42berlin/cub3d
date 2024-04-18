#ifndef CUB3D_FUNCS_H
# define CUB3D_FUNCS_H

/* main */

int		init_main_data(t_main_data *main_data, int argc, char *argv[]);

/* parse map */

int		parse_main(t_main_data *main_data);
int		parse_map(t_main_data *main_data, t_list_d *file_lbl);
int		init_parse_state(t_parse_state *parse_state, t_main_data *main_data,
			t_list_d *file_lbl);
int		init_parse_state_gen(t_parse_state *parse_state, t_main_data *main_data,
			t_list_d *file_lbl);
int		init_parse_state_map(t_parse_state *parse_state);
int		init_parse_state_tex(t_parse_state *parse_state);
int		init_parse_state_col(t_parse_state *parse_state);
int		identify_line(t_parse_state *parse_state);

/* parse util */

bool	compare_line(t_parse_state *parse_state, const char *str);
bool	is_newline(t_parse_state *parse_state);
bool	is_c(t_parse_state *parse_state);
bool	is_f(t_parse_state *parse_state);
bool	is_map_start(t_parse_state *parse_state);
bool	is_no(t_parse_state *parse_state);
bool	is_so(t_parse_state *parse_state);
bool	is_we(t_parse_state *parse_state);
bool	is_ea(t_parse_state *parse_state);
int		go_to_next_line(t_parse_state *parse_state);

/* errors */

int		throw_error_gen(int code, char *msg, bool exit_program);
int		throw_error_sys_call(t_error_ms error_info, bool exit_program);
int		throw_error_map_file(int code, t_parse_state *parse_state,
			bool exit_program);
char	*get_failed_func_str(enum e_failed_func failed_func);

/////////////////////////////////////////
/////// raycast folder friedrich ////////
/////////////////////////////////////////


/* clean.c */
void destroy_window(t_main_data *data);
int close_window(void *param);

/* color_buffer.c */
void fill_color_buffer(u_int32_t color, u_int32_t *color_buffer);

/* draw_line.c */
void draw_line_on_image(int *addr, int width, int height, int start_x, int start_y, int end_x, int end_y, int color);

/* draw_minimap.c */
void draw_map(t_main_data *data, int *addr);
void draw_tile(int *addr, int tile_x, int tile_y, int tile_color, t_main_data *data);
void draw_rays(t_main_data *data, int *addr, t_ray *rays);

/* draw_player.c */
void draw_player_direction(t_main_data *data, int *addr);
void draw_player(t_main_data *data, int *addr);

/* draw_render.c */
void render(t_main_data *data, int *addr, t_ray *rays);
int draw(t_main_data *data);

/* keys.c */
int keys(int key, void *param);

/* init.c */
void init_player(t_main_data *data);
void setup(t_main_data *data);
int initialize_window(t_main_data *data);
int init(t_main_data *data);

/* math_utils.c */
float normalize_angle(float angle);
float distance_between_points(float x1, float y1, float x2, float y2);

/* raycast.c */
void cast_ray(t_main_data *data, t_ray *rays, float ray_angle, int strip_id);
void cast_all_rays(t_main_data *data, t_ray *rays);

/* wall_ceiling_floor*/
void generate_3d_projection(t_main_data *data, t_ray *rays);

/* wall_collision.c */
int map_has_wall_at(float x, float y);


#endif
