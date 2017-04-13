
#include "list.h"

int		lst_rem_next(t_lst *list, t_lstelem *elem, void **data)
{
	t_lstelem *old_elem;

	if (lst_size(list) == 0)
		return (-1);
	if (elem == NULL)
	{
		*data = list->head->data;
		old_elem = list->head;
		list->head = list->head->next;
		if (list_size(list) == 1)
			list_tail = NULL;
	}
	else 
	{
		if (elem->next == NULL)
			return (-1);
		*data = elem->next->data;
		old_elem = elem->next;
		elem->next = elem->next->next;
		if (elem->next == NULL)
			list->tail = elem;
	}
	free(old_elem);
	list->size--;
	return (0);
}
