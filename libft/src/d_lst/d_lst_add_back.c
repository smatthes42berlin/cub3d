#include "lib_main.h"

void	d_lst_add_back(t_list_dc **lst, t_list_dc *new)
{
	t_list_dc	*last;

	if (!new)
		return ;
	last = d_lst_last(*lst);
	if (!*lst || !lst || !last)
	{
		*lst = new;
		new->next = NULL;
		new->prev = NULL;
		return ;
	}
	new->prev = last;
	new->next = NULL;
	last->next = new;
}
