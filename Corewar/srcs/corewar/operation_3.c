/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:33:45 by cpoulet           #+#    #+#             */
/*   Updated: 2017/03/28 17:34:46 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_vm *v, t_list *process)
{
	printf("Decale toi de : %hd\n", *(short*)&ARENA[PC + 1]);
}

void	op_fork(t_vm *v, t_list *process)
{
	(void)v;
	(void)process;
}

void	op_lfork(t_vm *v, t_list *process)
{
	(void)v;
	(void)process;
}
