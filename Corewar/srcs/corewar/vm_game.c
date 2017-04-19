
#include "corewar.h"

void kill_process(t_list **p, t_list *previous)
{
	previous->next = *p->next;	
	free(*p);
	*p = NULL;
}

void update_process(t_vm *v, t_list *process)
{
	if (BCTD)
		LIVE = 0;
	if (OP_CAST == 0)
		operate_process(v, process);
	else
		OP_CAST -= 1; // to optimize
}

void browse_processes_lst(t_vm *v) //pboutelo TODO : utilier ft_lstiter
{
	t_list *tmp;
	t_list *previous;	
	
	tmp = v->process_lst;
	while (tmp)
	{
		if (BCTD && !LIVE)
			kill_process(tmp, previous);		
		else
			update_process(v, tmp);
		previous = tmp;
		tmp = tmp->next; // si tmp == NULL car killed ? 
	}
}

void update_vm(t_vm *v)
{
	if (BCTD)
	{
		if (v->nlive_btcd >= NBR_LIVES)
		{
			v->cycle_to_die -= CYCLE_DELTA;
			v->is_ctd_modified = 1;
		}
		if (v->ncheck % MAX_CHECK == 0)	
		{
			if (!v->is_ctd_modified && v->ncheck != 0)
			{
				v->cycle_to_die--;
				v->is_ctd_modified = 0;
			}		
			if (v->ncheck != 0)
				v->ncheck = 0;
		}
		v->ncheck++;
	}
	v->ncycle++;
}

void run_game(t_vm *v)
{

	while (v->process_lst != NULL) 
	{
		printf("\ncycle = %d :\n", v->ncycle); // DEBUG
		browse_processes_lst(v);
		update_vm(v);
	}
}
		// each CYCLE_TO_DIE 
			// if nlives_btcd >= NBR_LIVES => CYCLE_TO_DIE -= CYCLE_DELTA;

		// count checks 
			// if nchecks CTD t(0) == nchecks CTD t(MAX_CHECK) => CYCLE_TO_DIE--; 

		// for each process 
			// if each CYCLE_TO_DIE live_count < 1 => kill the process 

