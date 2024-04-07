#ifndef CUB3D_FUNCS_H
# define CUB3D_FUNCS_H

/* main */

int				init_main_data(t_main_data *main_data, int argc, char *argv[]);

/* parse map */

int				parse_main(t_main_data *main_data);
int				parse_map_file(t_main_data *main_data, t_list_d *file_lbl);
int	init_parse_state(t_parse_state *parse_state,
						t_main_data *main_data,
						t_list_d *file_lbl);
int	init_parse_state_gen(t_parse_state *parse_state,
							t_main_data *main_data,
							t_list_d *file_lbl);
int				init_parse_state_map(t_parse_state *parse_state);
int				init_parse_state_optns(t_parse_state *parse_state);
int				init_optn(t_optn_parse *optn, const char *name,
					enum e_optn_type type);
int				identify_line(t_parse_state *parse_state);
int				handle_ceil(t_parse_state *parse_state);
int				handle_optn(t_parse_state *parse_state, t_optn_parse *optn);
int				handle_map_start(t_parse_state *parse_state);
int				get_map_max_dim(t_parse_state *parse_state);
int				handle_newline(t_parse_state *parse_state);
int				handle_unknown(t_parse_state *parse_state);
int				copy_array_from_file(t_parse_state *parse_state);
int				parse_whole_file(t_parse_state *parse_state);
int				parse_extracted_details(t_parse_state *parse_state);
bool			check_comma_error(t_optn_parse *col);
int				check_option_col(t_optn_parse *col);
int				get_val_rgb(t_optn_parse *col, char **splitted, int index);

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

/* errors */

int				throw_error_gen(int code, char *msg, bool exit_program);
int				throw_error_sys_call(t_error_ms error_info, bool exit_program);
int				throw_error_map_file(int code, t_parse_state *parse_state,
					bool exit_program);
char			*get_failed_func_str(enum e_failed_func failed_func);

/* free */

int				free_file_lbl(t_list_d **file_lbl);
int				free_parse_state(t_parse_state *parse_state);

/* print */

int				print_map(char **map, int width, int height);
int				print_parse_res(t_parse_state *parse_state);
int				print_optn_parse_res(t_optn_parse *optn);
int				print_map_parse_res(t_parse_state *parse_state);
int				print_gen_parse_res(t_parse_state *parse_state);
int				print_res(char *caption, bool val);
int				print_caption(char *caption);

/*raycast friedrich*/
int				keys(int key, void *param);
void			draw_map(t_main_data *data, int *addr);
void			draw_grid_lines(t_main_data *data, int *addr);
void			draw_player(t_main_data *data, int *addr);
int				max(int a, int b);
void			draw_line_on_image(int *addr, int width, int height,
					int start_x, int start_y, int end_x, int end_y, int color);
void			draw_vertical_rays(t_main_data *data, int *addr);
void			draw_horizontal_rays(t_main_data *data, int *addr);
void			create_window(t_main_data *data);
void			init_player(t_main_data *data);
void			init_map(t_main_data *data);
void			init(t_main_data *data);

int				draw(t_main_data *data);

#endif
