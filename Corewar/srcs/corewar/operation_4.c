/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/20 23:15:32 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_adv(t_vm *v, t_list *process, int shift)
{
	int	i;

	i = -1;
	if (v->display_mode == 1)
		printf("ADV %d (0x%04x -> 0x%04x) ", shift, PC, (PC + shift) % MEM_SIZE);
	while (++i < shift)
		printf("%02x ", ARENA(PC + i));
	printf("\n");
}

void	op_ldi(t_vm *v, t_list *process)
{
	u_char arg_nb;
	u_char	type;
	u_char	shift;
	int		val[3];

	arg_nb = 3;
	shift = 0;
	if (check_arg(9, B_OCT, arg_nb))
	{
		while (arg_nb)
		{
			type = (B_OCT >> (arg_nb-- * 2)) & 0b11;
			if (type == 1 && (ARENA(PC + 2 + shift) >= 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[arg_nb] = !arg_nb ? ARENA(PC + 2 + shift) - 1 :
				get_ar(v, process, &shift, type + 4); //+ 4 -> direct code sur 2 oct
			if (!arg_nb)
			{
				REG[val[0]] = reverse_bytes(v, PC + (val[1] + val[2]) % IDX_MOD, 4);
				CARRY = REG[val[0]] ? 0 : 1;
			}
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 2, 3)) % MEM_SIZE;
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
				shift = reverse_bytes(v, PC + 2, 4);
			else
			{
				shift = reverse_bytes(v, PC + 2, 2);
				shift = reverse_bytes(v, PC + shift, 4);
			}
			REG[ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) - 1] = shift;
			if (v->display_mode == 1)
				printf("val_saved = %x\n", shift);
			CARRY = shift ? 0 : 1;
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 4, arg_nb)) % MEM_SIZE;
}

void	op_lldi(t_vm *v, t_list *process)
{
	u_char arg_nb;
	u_char	type;
	u_char	shift;
	int		val[3];

	arg_nb = 3;
	shift = 0;
	if (check_arg(13, B_OCT, arg_nb))
	{
		while (arg_nb)
		{
			type = (B_OCT >> (arg_nb-- * 2)) & 0b11;
			if (type == 1 && (ARENA(PC + 2 + shift) >= 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[arg_nb] = !arg_nb ? ARENA(PC + 2 + shift) - 1 :
				get_ar(v, process, &shift, type + 4); //+ 4 -> direct code sur 2 oct
			if (!arg_nb)
			{
				REG[val[0]] = reverse_bytes(v, PC + val[1] + val[2], 4);
				CARRY = REG[val[0]] ? 0 : 1;
				if (v->display_mode == 1)
					printf("P%5d | REG[%d] = %x\n", NPRO, val[0], REG[val[0]]);
			}
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 2, 3)) % MEM_SIZE;
}

void	op_sti(t_vm *v, t_list *process)
{
	u_char	arg_nb;
	u_char	type;
	u_char	shift;
	int		val[3];
	u_char	save;

	arg_nb = 3;
	shift = 0;
	save = B_OCT; //in case of writing on B_OCT
	if (check_arg(10, B_OCT, arg_nb))
	{
		while (arg_nb)
		{
			type = (B_OCT >> (arg_nb-- * 2)) & 0b11;
			if (type == 1 && (ARENA(PC + 2 + shift) >= 16 || !ARENA(PC + 2 + shift)))
				break ;
			if (arg_nb == 2)
				val[arg_nb] = ARENA(PC + 2 + shift++) - 1;
			else
				val[arg_nb] = get_ar(v, process, &shift, type + 4); //+ 4 -> direct code sur 2 oct
			if (!arg_nb)
			{
				print_reg(v, process, REG[val[2]], PC + ((val[0] + val[1]) % IDX_MOD) + 3);
				if (v->display_mode == 1)
				{
					printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n",
					NPRO, val[2] + 1, val[1], val[0], val[1], val[0], (val[0] + val[1]) % IDX_MOD, PC +
					((val[0] + val[1]) % IDX_MOD));
					print_adv(v, process, octal_shift(process, B_OCT, 2, 3));
				}
			}
		}
	}
	PC = (PC + octal_shift(process, save, 2, 3)) % MEM_SIZE;
}