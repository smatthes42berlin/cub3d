#include "cub3d.h"

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

int	throw_error_map_file(int code, char *msg, bool exit_program)
{
	ft_printf_fd(2, "ERROR\n");
	ft_printf_fd(2, "%s\n", msg);
	if (exit_program)
		exit(code);
	return (code);
}