#include "libft.h"

int ft_lstlen(t_list *alst) // to move in libft
{
	int len;
	
	len = 0;
	while (alst)
	{
		len++;
		alst = alst->next;
	}
	return (len);
}
