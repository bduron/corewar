/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:18:18 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/25 08:55:18 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void update_process(t_vm *v, t_list *process)
{
	if (!OP_CAST)
	{
		if (0 <= NEXT_OP && NEXT_OP < 16)
			op_tab[NEXT_OP].f(v, process);
		else
			PC = (PC + 1) % MEM_SIZE;
	}
	OP_CAST -= 1;
	LIVE_SINCE++;
}

void kill_processes_lst(t_vm *v) // VERBOSE DONE
{
	t_list *process;
	t_list *previous;

	process = v->process_lst;
	previous = NULL;
	while (process)
	{
		if (!LIVE || v->cycle_to_die < 0)
		{
			if (process == v->process_lst)
			{
				v->process_lst = process->next;
				if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_DEATH))
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", NPRO, LIVE_SINCE, v->cycle_to_die);
				free(process->content);
				free(process);
				process = v->process_lst;
				previous = NULL;
			}
			else
			{
				if (v->display_mode == 1 && process && (v->verbose_param & FLAG_VERBOSE_DEATH))
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", NPRO, LIVE_SINCE, v->cycle_to_die);
				process = process->next;
				free(previous->next->content);
				free(previous->next);
				previous->next = process;
			}
			--v->nprocess_alive;
		}
		else
		{
			LIVE = 0;
			previous = process;
			process = process->next;
		}
	}
}

void browse_processes_lst(t_vm *v)
{
	t_list *process;

	process = v->process_lst;
	while (process)
	{
		update_process(v, process);
		process = process->next;
	}
	process = v->process_lst;
	while (process)
	{
		if (OP_CAST < 0)
			init_next_op(v, process);
		process = process->next;
	}
}

void update_vm(t_vm *v)
{
	if (BCTD)
	{
		v->is_ctd_modified = 0;
		if (v->nlive_bctd >= NBR_LIVE)
		{
			v->cycle_to_die -= CYCLE_DELTA;
			v->is_ctd_modified = 1;
			if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_CYCLES))
				ft_printf("Cycle to die is now %d\n", v->cycle_to_die);
		}
		v->ncheck = v->is_ctd_modified ? 0 : v->ncheck + 1;
		if (v->ncheck % MAX_CHECKS == 0)
		{
			if (!v->is_ctd_modified && v->ncheck != 0)
			{
				v->cycle_to_die -= CYCLE_DELTA;
				if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_CYCLES))
					ft_printf("Cycle to die is now %d\n", v->cycle_to_die);
			}
		}
		v->nlive_bctd = 0;
		v->ncycle_mod = 0;
	}
	v->ncycle++;
	v->ncycle_mod++;
}

void run_game(t_vm *v)
{
	t_list *process;

	process = v->process_lst;
	while (process)
	{
		init_next_op(v, process);
		process = process->next;
	}

	while (v->process_lst != NULL)
	{
		if (v->ncycle == v->dump_param)
		{
			print_arena(v);
			break ;
		}
		update_vm(v);
			if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_CYCLES))
				ft_printf("It is now cycle %d\n", v->ncycle);
		if (v->process_lst)
		{
			browse_processes_lst(v);
			if ((BCTD) || v->cycle_to_die < 0)
				kill_processes_lst(v);
		}
	}
	if (v->ncycle != v->dump_param)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		v->last_live_id + 1, v->p[v->last_live_id].name);
}

/*
 ** each CYCLE_TO_DIE
 ** if nlives_btcd >= NBR_LIVES => CYCLE_TO_DIE -= CYCLE_DELTA;
 **
 ** count checks
 ** if nchecks CTD t(0) == nchecks CTD t(MAX_CHECK) => CYCLE_TO_DIE--;
 **
 ** for each process
 ** if each CYCLE_TO_DIE live_count < 1 => kill the process
 */
