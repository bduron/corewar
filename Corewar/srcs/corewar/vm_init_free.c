
#include "corewar.h"

void vm_init(t_vm *v)
{
	int i;

	ft_memset(v->arena, 0, sizeof(unsigned char) * MEM_SIZE);
	ft_memset(v->arena_fmt, -1, sizeof(unsigned char) * MEM_SIZE);
	v->process_lst = NULL;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		v->p[i].nplayer = 0;
		ft_memset(v->p[i].name, 0, PROG_NAME_LENGTH);
		ft_memset(v->p[i].comment, 0, COMMENT_LENGTH);
		ft_memset(v->p[i].code, 0, CHAMP_MAX_SIZE);
		i++;
	}
}

void vm_free(t_vm *v)
{
	(void)v;
}
