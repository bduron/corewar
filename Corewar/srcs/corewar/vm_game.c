
#include "corewar.h"

//void kill_process(t_list **p, t_list **previous)
//{
//	(*previous)->next = (*p)->next;	
//	free(*p);
//	*p = NULL;
//}

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
	t_list *process;
	t_list *previous;	
	
	process = v->process_lst;
	previous = NULL;
	while (process)
	{
		if ((BCTD && !LIVE) || v->cycle_to_die < 0)
		{
	//		kill_process(&process, &previous);		
			if (process == v->process_lst) 
			{
				v->process_lst = process->next;
			//	KILL(process);
				if (process) 
					printf("Process %d hasn't lived for %d cycles (CTD %d)\n", NPRO, v->ncycle, v->cycle_to_die);
				process = v->process_lst;
			}
			else
			{
				process = process->next;
			//	KILL(prev->next);
				if (process) 
					printf("Process %d hasn't lived for %d cycles (CTD %d)\n", NPRO, v->ncycle, v->cycle_to_die);
				previous->next = process;
			}
		}
		else
		{
			update_process(v, process);
			process = process->next;
			previous = process;
		}
	}
}

void update_vm(t_vm *v)
{	
	if (BCTD)
	{ 
		v->is_ctd_modified = 0;
		//printf("================\nCTD = %d\nnlive_bctd = %d\nncheck = %d\n================\n", v->cycle_to_die, v->nlive_bctd, v->ncheck);
		if (v->nlive_bctd >= NBR_LIVE)
		{	
			//printf("nblive emis total\n");
			v->cycle_to_die -= CYCLE_DELTA;
			v->is_ctd_modified = 1;
			printf("Cycle to die is now %d\n", v->cycle_to_die); // DEBUG
		}
		v->ncheck = v->is_ctd_modified ? 0 : v->ncheck + 1;
		if (v->ncheck % MAX_CHECKS == 0)
		{
			if (!v->is_ctd_modified && v->ncheck != 0)
			{
				v->cycle_to_die -= CYCLE_DELTA;
				printf("Cycle to die is now %d\n", v->cycle_to_die); // DEBUG
			}
		}
		v->nlive_bctd = 0;
	//	printf("A===============\nCTD = %d\nnlive_bctd = %d\nncheck = %d\n================\n", v->cycle_to_die, v->nlive_bctd, v->ncheck);
		v->ncycle_mod = 0;
	}
	v->ncycle++;
	v->ncycle_mod++;
}

void run_game(t_vm *v)
{

	while (v->process_lst != NULL) //cpoulet : checker la position du C_T_D par rapport au browse
	{
		printf("It is now cycle %d\n", v->ncycle); // DEBUG
		if (v->process_lst)
			browse_processes_lst(v);
		update_vm(v);
//		if (v->cycle_to_die < 0) //cpoulet modif to be confirmed
//			break;
	}
	printf("Contestant %d, \"%s\", has won !\n", -v->p[v->last_live_id].nplayer, v->p[v->last_live_id].name);
}
		// each CYCLE_TO_DIE 
			// if nlives_btcd >= NBR_LIVES => CYCLE_TO_DIE -= CYCLE_DELTA;

		// count checks 
			// if nchecks CTD t(0) == nchecks CTD t(MAX_CHECK) => CYCLE_TO_DIE--; 

		// for each process 
			// if each CYCLE_TO_DIE live_count < 1 => kill the process 

