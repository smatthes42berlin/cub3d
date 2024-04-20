#ifndef CUB3D_FUNCS_H
# define CUB3D_FUNCS_H

/* main */

int				init_main_data(t_main_data *main_data, int argc, char *argv[]);

/* parse map */

int				parse_main(t_main_data *main_data);
int				parse_map_file(t_main_data *main_data, t_list_dc *file_lbl);
int	init_parse_state(t_parse_state *parse_state,
						t_main_data *main_data,
						t_list_dc *file_lbl);
int	init_parse_state_gen(t_parse_state *parse_state,
							t_main_data *main_data,
							t_list_dc *file_lbl);
int				init_parse_state_map(t_parse_state *parse_state);
int				init_parse_state_optns(t_parse_state *parse_state);
int				init_optn(t_optn_parse *optn, const char *name,
					enum e_optn_type type, t_parse_state *parse_state);
int				identify_line(t_parse_state *parse_state);
int				handle_ceil(t_parse_state *parse_state);
int				handle_optn(t_parse_state *parse_state, t_optn_parse *optn);
int				handle_map_start(t_parse_state *parse_state);
int				get_map_max_dim(t_parse_state *parse_state);
int				handle_newline(t_parse_state *parse_state);
int				handle_unknown(t_parse_state *parse_state);
int				copy_array_from_file(t_parse_state *parse_state);
int				parse_whole_file(t_parse_state *parse_state);

/* check validity */

int				check_extracted_details(t_parse_state *parse_state);
int				check_map_validity(t_parse_state *parse_state);
int				check_option_col(t_optn_parse *col);
int				check_option_tex(t_optn_parse *col);
int				check_file_access(t_optn_parse *col);
int				check_path_extension(t_optn_parse *col);
int				check_path_format(t_optn_parse *col);
int				handle_unquoted_path(t_optn_parse *col);
int				handle_quoted_path(t_optn_parse *col);
int				get_val_rgb(t_optn_parse *col, char **splitted, int index);
bool			check_comma_error(t_optn_parse *col);
int				check_exactly_one_start_pos(t_parse_state *parse_state);
int				check_unknown_characters(t_parse_state *parse_state);
int				get_start_pos(t_parse_state *parse_state, int height, int width,
					int *num_start_pos);
int				set_start_pos_n_angle(t_parse_state *parse_state, char orient,
					float angle);
int				undo_flood_fill(t_parse_state *parse_state);
int				create_reachable_map(t_parse_state *parse_state);

/* check parse res */

int				check_parse_res_main(t_parse_state *parse_state);
int				print_error_msg(t_parse_state *parse_state, char *msg,
					const char *identifier);
int				check_gen_errors(t_parse_state *parse_state);
int				check_map_errors(t_parse_state *parse_state);
int	check_option_errors(t_parse_state *parse_state,
						t_optn_parse *optn);

/* flood fill it */

int				flood_fill_it(t_parse_state *parse_state);
int				flood_check_it(t_parse_state *parse_state);
int				add_point_to_queue(t_parse_state *parse_state, int height,
					int width);
int				remove_point_from_queue(t_parse_state *parse_state);
int	get_cur_point_queue(t_parse_state *parse_state,
						int cur_point[2]);
int	add_surrounding_points_queue(t_parse_state *parse_state,
									int *cur_point);
bool	check_point_needs_test(t_parse_state *parse_state,
							int *cur_point);

/* flood fill rec */

int				flood_fill_rec(t_parse_state *parse_state);
int				flood_check(t_parse_state *parse_state, int height, int width,
					int rec_depth);

/* flood fill rec lim */

int				flood_fill_rec_lim(t_parse_state *parse_state);
int				flood_check_rec_lim(t_parse_state *parse_state, int height,
					int width, int rec_depth);
bool	check_end_point_reached(t_parse_state *parse_state, int cur_point[2]);
int	recursion_surrounding_points(t_parse_state *parse_state, int cur_point[2], int rec_depth);



/* flood fill util */

int				adjust_reachable_map(t_parse_state *parse_state, int height,
					int width);
int				check_map_not_closed(t_parse_state *parse_state, int height,
					int width);

/* parse util */

bool			compare_line(t_parse_state *parse_state, const char *str);
bool			is_newline(t_parse_state *parse_state);
bool			is_map_start(t_parse_state *parse_state);
t_optn_parse	*is_optn(t_parse_state *parse_state);
int				go_to_next_line(t_parse_state *parse_state);
int				get_cur_line_trimmed(t_parse_state *parse_state);
bool	optn_not_def_map_not_started(t_parse_state *parse_state,
									t_optn_parse *optn);
bool			optn_alr_def(t_optn_parse *optn);
bool			map_already_ended(t_parse_state *parse_state);
bool			is_quote(char c);
bool			closing_quote_found(char *cli_input, char quote_type);
bool			closing_quote_not_last_char(t_optn_parse *col);
int				set_bool_field(bool *field, bool val, int code);

/* check validity */

/* errors */

int				throw_error_gen(int code, char *msg, bool exit_program);
int				throw_error_sys_call(t_error_ms error_info, bool exit_program);
int	throw_error_sys_call_parse(t_error_ms error_info,
								t_parse_state *parse_state,
								bool exit_program);
int				throw_error_map_file(int code, t_parse_state *parse_state,
					bool exit_program);
char			*get_failed_func_str(enum e_failed_func failed_func);

/* free */

int				free_file_lbl(t_list_dc **file_lbl);
int				free_parse_state(t_parse_state *parse_state);

/* print */

int				print_map(char **map, int width, int height);
int				print_parse_res(t_parse_state *parse_state);
int				print_optn_parse_res(t_optn_parse *optn);
int				print_map_parse_res(t_parse_state *parse_state);
int				print_gen_parse_res(t_parse_state *parse_state);
int				print_res(char *caption, bool val);
int				print_caption(char *caption);
int				print_map_parsing(t_parse_state *parse_state, const char which);

/////////////////////////////////////////
/////// raycast folder friedrich ////////
/////////////////////////////////////////

/* clean.c */
void			destroy_window(t_main_data *data);
int				close_window(void *param);

/* color_buffer.c */
void			fill_color_buffer(u_int32_t color, u_int32_t *color_buffer);

/* draw_line.c */
void			draw_line_on_image(int *addr, int width, int height,
					int start_x, int start_y, int end_x, int end_y, int color);

/* draw_minimap.c */
void			draw_map(t_main_data *data, int *addr);
void			draw_tile(int *addr, int tile_x, int tile_y, int tile_color,
					t_main_data *data);
void			draw_rays(t_main_data *data, int *addr, t_ray *rays);

/* draw_player.c */
void			draw_player_direction(t_main_data *data, int *addr);
void			draw_player(t_main_data *data, int *addr);

/* draw_render.c */
void			render(t_main_data *data, int *addr, t_ray *rays);
int				draw(t_main_data *data);

/* keys.c */
int				keys(int key, void *param);

/* init.c */
void			init_player(t_main_data *data);
void			init_map(t_main_data *data);
void			setup(t_main_data *data);
int				initialize_window(t_main_data *data);
int				init(t_main_data *data);

/* math_utils.c */
float			normalize_angle(float angle);
float			distance_between_points(float x1, float y1, float x2, float y2);

/* raycast.c */
void			cast_ray(t_main_data *data, t_ray *rays, float ray_angle,
					int strip_id);
void			cast_all_rays(t_main_data *data, t_ray *rays);

/* wall_ceiling_floor*/
void			generate_3d_projection(t_main_data *data, t_ray *rays);

/* wall_collision.c */
int				map_has_wall_at(t_main_data *data, float x, float y);

#endif
