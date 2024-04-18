#include "lib_main.h"

t_list_dc	*d_lst_pop_n(t_list_dc **lst, int n)
{
	t_list_dc	*to_pop;
	int			size;

	if (!lst || !*lst)
		return (NULL);
	size = d_lst_size(*lst);
	if (n > size - 1)
		return (NULL);
	if (n == -1)
		n = size;
	if (n == 0)
		return (d_lst_pop(lst));
	to_pop = *lst;
	while (n > 0)
	{
		to_pop = to_pop->next;
		n--;
	}
	to_pop->prev->next = to_pop->next;
	if (to_pop->next)
		to_pop->next->prev = to_pop->prev;
	to_pop->next = NULL;
	to_pop->prev = NULL;
	return (to_pop);
}
