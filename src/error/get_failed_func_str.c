#include "cub3d.h"

// static char	*get_failed_func_str_2(enum e_failed_func failed_func);

char	*get_failed_func_str(enum e_failed_func failed_func)
{
	if (failed_func == ERROR_OPEN)
		return ("ERROR_OPEN");
	if (failed_func == ERROR_READ)
		return ("ERROR_READ");
	if (failed_func == ERROR_WRITE)
		return ("ERROR_WRITE");
	if (failed_func == ERROR_PRINTF)
		return ("ERROR_PRINTF");
	if (failed_func == ERROR_MALLOC)
		return ("ERROR_MALLOC");
	if (failed_func == ERROR_FREE)
		return ("ERROR_FREE");
	if (failed_func == ERROR_PERROR)
		return ("ERROR_PERROR");
	if (failed_func == ERROR_STRERROR)
		return ("ERROR_STRERROR");
	if (failed_func == ERROR_EXIT)
		return ("ERROR_EXIT");
	return (NULL);
	// return (get_failed_func_str_2(failed_func));
}

// char	*get_failed_func_str_2(enum e_failed_func failed_func)
// {
// 	return (NULL);
// }
