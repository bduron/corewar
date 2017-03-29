/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/03/29 11:23:41 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_vm *v, t_list *process)
{
	int live;

	LIVE++; // maybe uniquement dans le cas ou le numero du live correspond a un playeur valide
	live = reverse_bytes(&ARENA[PC + 1], 4);
	printf("LIVE : %x\n", live);
}

void	op_ld(t_vm *v, t_list *process)
{
	int	val;

	if (ARENA[PC + 1] != 0x90 && ARENA[PC + 1] != 0xd0)
		octal_error(process, 5);
	else if (ARENA[PC + 6 - ((ARENA[PC + 1] & 0x60) >> 5)] >= 16)
		octal_error(process, 5); //registre non compris entre 0 et 15
	else
	{
		val = reverse_bytes(&ARENA[PC + 2], 4 - ((ARENA[PC + 1] & 0x60) >> 5));
		val = (val && ARENA[PC + 1] == 0xd0) ? val % IDX_MOD : val;
		printf("val = %d\n", val);
		REG[ARENA[PC + 6 - ((ARENA[PC + 1] & 0x60) >> 5)] - 1] =
			(ARENA[PC + 1] == 0x90) ? val : ARENA[PC + val];
	}
}

void	op_st(t_vm *v, t_list *process)
{
	int octal;

	octal = ARENA[PC + 1];
	if (octal != 0x50 && octal != 0x70)
		octal_error(process, 5);
}

void	op_aff(t_vm *v, t_list *process)
{
	if (ARENA[PC + 1] != 0x40 || ARENA[PC + 2] < 1 || ARENA[PC + 2] >= 16)
		octal_error(process, 3);
	else
	{
		printf("aff = |%d|\n", (unsigned char)REG[ARENA[PC + 2] - 1]);
		PC += 3;
	}
}
