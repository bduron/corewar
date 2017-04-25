
#include "libft.h"

void    ft_strsplitdel(char **split) // Ajouter a la lib
{
	int i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}
