#include "cub3d.h"

int	throw_error_sys_call_parse(t_error_ms error_info,
								t_parse_state *parse_state,
								bool exit_program)
{
	free_parse_state(parse_state);
	return (throw_error_sys_call(error_info, exit_program));
}

int	throw_error_sys_call(t_error_ms error_info, bool exit_program)
{
	ft_printf_fd(2, "ERROR\n");
	ft_printf_fd(2, "errno msg: %s\n", strerror(error_info.err_code));
	ft_printf_fd(2, "Failed Func: %s\n",
			get_failed_func_str(error_info.failed_func));
	if (error_info.add_info)
		ft_printf_fd(2, "Add Info: %s\n", error_info.add_info);
	if (exit_program)
		exit(error_info.err_code);
	return (error_info.err_code);
}

int	throw_error_gen(int code, char *msg, bool exit_program)
{
	ft_printf_fd(2, "ERROR\n");
	ft_printf_fd(2, "%s\n", msg);
	if (exit_program)
		exit(code);
	return (code);
}

int	throw_error_map_file(int code, t_parse_state *parse_state,
		bool exit_program)
{
	ft_printf_fd(2, "ERROR\n");
	ft_printf_fd(2, "%s\n", "Print specific parsing error here");
	ft_printf_fd(2, "%d\n", parse_state->defs_after_map_found);
	if (exit_program)
		exit(code);
	return (code);
}