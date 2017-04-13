
#include "corewar.h"

void update_process(t_vm *v, t_list *process)
{
	if (OP_CAST == 0)
		operate_process(v, process);
		//launch_op
	else
		OP_CAST -= 1; // to optimize
}

void browse_processes_lst(t_vm *v)
{
	t_list *tmp;

	tmp = v->process_lst;
	while (tmp)
	{
		update_process(v, tmp);
		tmp = tmp->next;
	}

}

void run_game(t_vm *v)
{
	int i;

	i = 0;
	while (++i < 50)//v->nlive_bctd != 0) // condition modif
	{
		printf("\ncycle = %d :\n", v->ncycle);
		v->ncycle++;
		browse_processes_lst(v);
	}
}
