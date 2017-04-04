/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/04 12:14:56 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ldi(t_vm *v, t_list *process)
{
	u_char arg_nb;

	arg_nb = 3;
	if (check_arg(9, B_OCT, arg_nb))
	{
		(void)v;
		//CARRY = XXX ? 0 : 1;
	}
	octal_shift(process, B_OCT, 2, arg_nb);
}

void	op_lld(t_vm *v, t_list *process)
{
	u_char	arg_nb;
	int		shift;

	arg_nb = 2;
	if (check_arg(12, B_OCT, arg_nb))
	{
		if ((ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) >= 1) &&
				(ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) <= 16))
		{
			if (B_OCT == 0x90)
				shift = reverse_bytes(&ARENA((PC + 2)), 4);
			else
			{
				shift = reverse_bytes(&ARENA(PC + 2), 2);
				shift = reverse_bytes(&ARENA((PC + shift)), 4);
			}
			REG[ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) - 1] = shift;
			printf("val_saved = %x\n", shift); //DEBUG
			CARRY = shift ? 0 : 1;
		}
	}
	octal_shift(process, B_OCT, 4, arg_nb);
}

void	op_lldi(t_vm *v, t_list *process)
{
	u_char arg_nb;

	arg_nb = 3;
	if (check_arg(13, B_OCT, arg_nb))
	{
		(void)v;
	}
	octal_shift(process, B_OCT, 2, arg_nb);
}

void	op_sti(t_vm *v, t_list *process)
{
	u_char arg_nb;

	arg_nb = 3;
	if (check_arg(10, B_OCT, arg_nb))
	{
		(void)v;
	}
	octal_shift(process, B_OCT, 2, arg_nb);
}
