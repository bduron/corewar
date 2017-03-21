
#include "corewar.h"


void load_processes(tm_v *v)
{
	t_process p;
	int i;

	i = 0;
	while (i < v->nplayer)	
	{
		ft_lstappend(&(v->process_lst), ft_lstnew(&p, sizeof(t_process)));
		v->process_lst->content->carry = 0;			
		v->process_lst->content->pc = 0;			
		v->process_lst->content->op_cast = 0;			
		v->process_lst->content->live_count = 0;			
	}




}

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
		ft_memcpy(&(v->a.arena[i]), v->p[n].code, v->p[n].prog_len);
		ft_memset(&(v->a.owner[i]), n, v->p[n].prog_len);
		i += space;
		n++;
	}
}

void load_arena(t_vm *v)
{
	load_champions(v);
	//load_processes(v);
}

