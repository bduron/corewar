#include "list.h"

void	lst_destroy(t_lst *list)
{
	void *data;

	while (list_size(list) > 0)	
	{
		if (lst_rem_next(list, NULL, (void **)&data) == 0
			&& list->destroy != NULL)
			list->destroy(data);
	}
	ft_memset(list, 0, sizeof(list));
	return ;
}
