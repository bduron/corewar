/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/04 12:24:18 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_vm *v, t_list *process)
{
	int live;

	LIVE++; // maybe uniquement dans le cas ou le numero du live correspond a un playeur valide
	live = reverse_bytes(&ARENA(PC + 1), 4);
	printf("LIVE : %x\n", live);
	octal_shift(process, B_OCT, 4, 1);
}

void	op_ld(t_vm *v, t_list *process)
{
	int shift;

	if (B_OCT == 0x90 || B_OCT == 0xd0)
	{
		if ((ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) >= 1) &&
			(ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) <= 16))
		{
			if (B_OCT == 0x90)
				shift = reverse_bytes(&ARENA((PC + 2)), 4);
			else
			{
				shift = reverse_bytes(&ARENA(PC + 2), 2);
				shift %= IDX_MOD;
				shift = reverse_bytes(&ARENA((PC + shift)), 4);
			}
			REG[ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) - 1] = shift;
			printf("val_saved = %x\n", shift);
			CARRY = shift ? 0 : 1;
		}
	}
	octal_shift(process, B_OCT, 4, 2);
}

void	op_st(t_vm *v, t_list *process)
{
	int				shift;
	unsigned int	val;

	if ((B_OCT == 0x50 || B_OCT == 0x70) && ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16)
	{
		if (B_OCT == 0x50 && ARENA(PC + 3) >= 1 && ARENA(PC + 3) <= 16)
			REG[ARENA(PC + 3) - 1] = REG[ARENA(PC + 2) - 1];
		else if (B_OCT == 0x70)
		{
			shift = reverse_bytes(&ARENA(PC + 3), 2);
			shift %= IDX_MOD;
			val = REG[ARENA(PC + 2) - 1];
			while (val)
			{
				ARENA((PC + shift-- + 3)) = val & 0xFF;
				val >>= 8;
			}
		}
	}
	print_arena(v); //DEBUG
	octal_shift(process, B_OCT, 4, 2);
}

void	op_aff(t_vm *v, t_list *process)
{
	if (B_OCT == 0x40 && ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16)
		printf("aff = |%d|\n", (u_char)REG[ARENA(PC + 2) - 1]); // a mettre au bon format output
	octal_shift(process, B_OCT, 4, 1);
}
