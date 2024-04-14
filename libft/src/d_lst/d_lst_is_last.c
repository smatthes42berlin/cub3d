#include "lib_main.h"

bool	d_lst_is_last(t_list_dc *lst)
{
	if (!lst)
		return (false);
	return (!lst->next);
}
