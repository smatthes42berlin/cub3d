#ifndef CUB3D_FUNCS_H
# define CUB3D_FUNCS_H

/* main */

int		init_main_data(t_main_data *main_data, int argc, char *argv[]);

/* parse map */

int		parse_main(t_main_data *main_data);
int		parse_map(t_main_data *main_data, t_list_d *file_lbl);

/* errors */

int		throw_error_sys_call(t_error_ms error_info, bool exit_program);
int		throw_error_map_file(int code, char *msg, bool exit_program);
char	*get_failed_func_str(enum e_failed_func failed_func);

#endif
