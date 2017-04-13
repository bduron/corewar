
#include "list.h"

void	lst_init(t_lst *list, (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	return ;
}
