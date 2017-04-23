/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/23 17:06:58 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ldi(t_vm *v, t_list *process) // VERBOSE DONE
{
	u_char	arg_nb;
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
				if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
					ft_printf("P %4d | ldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n",
					NPRO, val[2], val[1], val[0] + 1, val[2], val[1], val[2] + val[1], PC +
					((val[1] + val[2]) % IDX_MOD));
			}
		}
	}
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 2, 3));
	PC = (PC + octal_shift(B_OCT, 2, 3)) % MEM_SIZE;
}

void	op_lld(t_vm *v, t_list *process) // VERBOSE DONE
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
				shift = reverse_bytes(v, PC + shift, 2);
			}
			REG[ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) - 1] = shift;
			if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
				ft_printf("P %4d | lld %d r%d\n", NPRO, shift, ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)));
			CARRY = shift ? 0 : 1;
		}
	}
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 4, arg_nb));
	PC = (PC + octal_shift(B_OCT, 4, arg_nb)) % MEM_SIZE;
}

void	op_lldi(t_vm *v, t_list *process) // VERBOSE DONE
{
	u_char	arg_nb;
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
				if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
					ft_printf("P %4d | lldi %d %d r%d\n       | -> load from %d + %d = %d (with pc %d)\n",
						NPRO, val[2], val[1], val[0] + 1, val[2], val[1], val[2] + val[1], PC + val[2] + val[1]);
			}
		}
	}
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 2, 3));
	PC = (PC + octal_shift(B_OCT, 2, 3)) % MEM_SIZE;
}

void	op_sti(t_vm *v, t_list *process) // VERBOSE DONE
{
	u_char	arg_nb;
	u_char	type;
	u_char	shift;
	int		val[3];
	u_char	save;

	arg_nb = 3;
	shift = 0;
	save = B_OCT; //in case of writing himself on B_OCT
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
				if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
					ft_printf("P %4d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n",
						NPRO, val[2] + 1, val[1], val[0], val[1], val[0], val[0] + val[1], PC +
						((val[0] + val[1]) % IDX_MOD));
			}
		}
	}
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(save, 2, 3));
	PC = (PC + octal_shift(save, 2, 3)) % MEM_SIZE;
}
