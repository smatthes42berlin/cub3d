#include "lib_main.h"

void	d_lst_add_front(t_list_dc **lst, t_list_dc *new)
{
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		new->prev = NULL;
		(*lst)->prev = new;
	}
	*lst = new;
}
