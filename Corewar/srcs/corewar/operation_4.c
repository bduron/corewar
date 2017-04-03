/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/03 16:17:04 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ldi(t_vm *v, t_list *process)
{
	size_t arg_nb;

	arg_nb = 3;
	if (check_arg(9, B_OCT, arg_nb))
	{
		(void)v;
	}
	octal_shift(process, B_OCT, 2, arg_nb);
}

void	op_lld(t_vm *v, t_list *process)
{
	size_t			arg_nb;
	unsigned int	val;

	arg_nb = 2;
	if (check_arg(12, B_OCT, arg_nb))
	{
		if ((ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) >= 1) &&
				(ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) <= 16))
		{
			val = reverse_bytes(&ARENA(PC + 2), 4 - ((B_OCT & 0x60) >> 5));
			val = B_OCT == 0x90 ? val : ARENA(PC + val);
			REG[ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) - 1] = val;
			printf("val = %d\n", val);
			CARRY = val ? 0 : 1;
		}
	}
	octal_shift(process, B_OCT, 4, arg_nb);
}

void	op_lldi(t_vm *v, t_list *process)
{
	size_t arg_nb;

	arg_nb = 3;
	if (check_arg(13, B_OCT, arg_nb))
	{
		(void)v;
	}
	octal_shift(process, B_OCT, 2, arg_nb);
}

void	op_sti(t_vm *v, t_list *process)
{
	size_t arg_nb;

	arg_nb = 3;
	if (check_arg(10, B_OCT, arg_nb))
	{
		(void)v;
	}
	octal_shift(process, B_OCT, 2, arg_nb);
}
