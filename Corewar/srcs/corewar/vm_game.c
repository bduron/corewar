
#include "corewar"



void update_process(t_vm *v, t_list *process) 
{
	if (((t_process *)process->content)->op_cast == 0)
		
		//decode_op 
		//launch_op 
	else 		
		((t_process *)process->content)->op_cast -= 1; // to optimize
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
	while (v->nlive_bctd != 0)
		browse_processes_lst(t_vm *v)
	
}
