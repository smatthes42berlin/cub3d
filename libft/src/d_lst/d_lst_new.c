#include "lib_main.h"

t_list_dc	*d_lst_new(void *content)
{
	t_list_dc	*lst_ptr;

	lst_ptr = malloc(sizeof(*lst_ptr));
	if (!lst_ptr)
		return (NULL);
	lst_ptr->next = NULL;
	lst_ptr->content = content;
	lst_ptr->prev = NULL;
	return (lst_ptr);
}
