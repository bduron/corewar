
#include "libft.h"

void	*ft_lstpop(t_list **alst)
{
	void *data;	
	t_list *tmp;

	if (!*alst)
		return (NULL);	
	data = (*alst)->content;
	tmp = *alst;	
	*alst = (*alst)->next;
	free(tmp);
	return data;
}
