
#include "corewar.h"


//void load_processes(tm_v *v)
//{
//	v->process_lst = ft_lstnew();
//
//
//
//
//}

void load_champions(t_vm *v)
{
	int space; 
	int i;
	int n;

	space = MEM_SIZE / v->nplayer;
	i = 0;
	n = 0;
	while (n < v->nplayer)
	{	
		ft_memcpy(&(v->arena[i]), v->p[n].code, v->p[n].prog_len);
		ft_memset(&(v->arena_fmt[i]), n, v->p[n].prog_len);
		i += space;
		n++;
	}
}

void load_arena(t_vm *v)
{
	load_champions(v);
	//load_processes(v);
}

