
#include "corewar.h"

void add_process(t_vm *v, t_list *process, unsigned int son_pc)
{
	t_process	son;
	int			k;

	++v->nprocess;
	ft_lstadd(&(v->process_lst), ft_lstnew(&son, sizeof(t_process)));
	((t_process *)v->process_lst->content)->carry = CARRY;
	((t_process *)v->process_lst->content)->nprocess = v->nprocess;
	((t_process *)v->process_lst->content)->pc = son_pc;
	((t_process *)v->process_lst->content)->live_count = LIVE; //TO BE CONFIRMED
	((t_process *)v->process_lst->content)->op_cast = 0;
	((t_process *)v->process_lst->content)->next_op = -1;
	k = 16;
	while (k--)
		((t_process *)v->process_lst->content)->reg[k] = REG[k];
}

void load_processes(t_vm *v)
{
	t_process p;
	int i;

	i = 0;
	while (i < v->nplayer)
	{
		++v->nprocess;
		ft_lstadd(&(v->process_lst), ft_lstnew(&p, sizeof(t_process))); // le dernier joueur aura le 1er processus dans l'ordre d'execution
		((t_process *)v->process_lst->content)->carry = 0; //  1 ou 0 telle est la question ? -> cpoulet : 0 !
		((t_process *)v->process_lst->content)->nprocess = v->nprocess;
		((t_process *)v->process_lst->content)->pc = v->p[i].pc_address; // addresse relative
		((t_process *)v->process_lst->content)->live_count = 0;
		((t_process *)v->process_lst->content)->op_cast = 0; // pboutelo : la 1ère action lu par les processus est déclenché au tour 0, initialisation à modifier
		((t_process *)v->process_lst->content)->next_op = -1; //cpoulet : 0 used by LIVE
		ft_memset(&(((t_process *)v->process_lst->content)->reg), 0, REG_NUMBER * sizeof(int));
		((t_process *)v->process_lst->content)->reg[0] = v->p[i].nplayer;
		i++;
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
		v->p[n].pc_address = i;
		i += space;
		n++;
	}
}

void load_arena(t_vm *v)
{
	load_champions(v);
	load_processes(v);
}
