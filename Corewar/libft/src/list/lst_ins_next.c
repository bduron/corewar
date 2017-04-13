
#include "list.h"

int		lst_ins_next(t_lst *list, t_lstelem *elem, const void *data)
{
	t_listelem *new_elem;

	if (new_elem = (t_lstelem *)malloc(sizeof(t_listelem)) == NULL)
		return (-1);

	new_elem->data = (void *)data;

	if (elem == NULL)
	{
		if (lst_size(list) == 0)
			list->tail = new_elem;
		new_elem->next = list->head;
		list->head = new_elem;
	}
	else 
	{
		if (elem->next == NULL)
			list->tail = new_elem;
		new_elem->next = elem->next;
		elem->next = new_elem;
	} 
	list->size++;
	return ;	
}
