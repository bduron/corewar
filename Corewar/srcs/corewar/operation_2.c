/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:32:40 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/20 18:48:06 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_add(t_vm *v, t_list *process)
{
	int		val;
	char	nb_arg;

	nb_arg = 3;
	if (check_arg(3, B_OCT, nb_arg))
	{
		if (ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16 &&
			ARENA(PC + 3) >= 1 && ARENA(PC + 3) <= 16 &&
			ARENA(PC + 4) >= 1 && ARENA(PC + 4) <= 16)
		{
			val = REG[ARENA(PC + 2) - 1] + REG[ARENA(PC + 3) - 1];
			if (v->display_mode == 1)
			{
				printf("P%5d | add r%d r%d r%d\n", NPRO, ARENA(PC + 2), ARENA(PC + 3), ARENA(PC + 4));
				print_adv(v, process, octal_shift(process, B_OCT, 4, nb_arg));
			}
			CARRY = val ? 0 : 1;
			REG[ARENA(PC + 4) - 1] = val;
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 4, nb_arg)) % MEM_SIZE;
}

void	op_sub(t_vm *v, t_list *process)
{
	int		val;
	char	nb_arg;

	nb_arg = 3;
	if (check_arg(4, B_OCT, nb_arg))
	{
		if (ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16 &&
			ARENA(PC + 3) >= 1 && ARENA(PC + 3) <= 16 &&
			ARENA(PC + 4) >= 1 && ARENA(PC + 4) <= 16)
		{
			val = REG[ARENA(PC + 2) - 1] - REG[ARENA(PC + 3) - 1];
			if (v->display_mode == 1)
			{
				printf("P%5d | sub r%d r%d r%d\n", NPRO, ARENA(PC + 2), ARENA(PC + 3), ARENA(PC + 4));
				print_adv(v, process, octal_shift(process, B_OCT, 4, nb_arg));
			}
			CARRY = val ? 0 : 1;
			REG[ARENA(PC + 4) - 1] = val;
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 4, nb_arg)) % MEM_SIZE;
}

void	op_and(t_vm *v, t_list *process)
{
	int		nb_arg;
	u_char	type;
	u_char	shift;
	int		val[3];

	nb_arg = 3;
	shift = 0;
	if (check_arg(5, B_OCT, nb_arg))
	{
		while (nb_arg)
		{
			type = (B_OCT >> (nb_arg-- * 2)) & 0b11;
			if (type == 1 && (ARENA(PC + 2 + shift) > 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[nb_arg] = !nb_arg ? ARENA(PC + 2 + shift) - 1 :
										get_ar(v, process, &shift, type);
			if (!nb_arg)
			{
				REG[val[0]] = val[1] & val[2];
				if (v->display_mode == 1)
				{
					printf("P%5d | and %d %d r%d\n", NPRO, val[2], val[1], val[0] + 1);
					print_adv(v, process, octal_shift(process, B_OCT, 4, 3));
				}
				CARRY = REG[val[0]] ? 0 : 1;
			}
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 4, 3)) % MEM_SIZE;
}

void	op_or(t_vm *v, t_list *process)
{
	int		nb_arg;
	u_char	type;
	u_char	shift;
	int		val[3];

	nb_arg = 3;
	shift = 0;
	if (check_arg(5, B_OCT, nb_arg))
	{
		while (nb_arg)
		{
			type = (B_OCT >> (nb_arg-- * 2)) & 0b11;
			if (type == 1 && (ARENA(PC + 2 + shift) > 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[nb_arg] = !nb_arg ? ARENA(PC + 2 + shift) - 1 :
										get_ar(v, process, &shift, type);
			if (!nb_arg)
			{
				REG[val[0]] = val[1] | val[2];
				if (v->display_mode == 1)
				{
					printf("P%5d | or %d %d r%d\n", NPRO, val[2], val[1], val[0] + 1);
					print_adv(v, process, octal_shift(process, B_OCT, 4, 3));
				}
				CARRY = REG[val[0]] ? 0 : 1;
			}
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 4, 3)) % MEM_SIZE;
}

void	op_xor(t_vm *v, t_list *process)
{
	int		nb_arg;
	u_char	type;
	u_char	shift;
	int		val[3];

	nb_arg = 3;
	shift = 0;
	if (check_arg(5, B_OCT, nb_arg))
	{
		while (nb_arg)
		{
			type = (B_OCT >> (nb_arg-- * 2)) & 0b11;
			if (type == 1 && (ARENA(PC + 2 + shift) > 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[nb_arg] = !nb_arg ? ARENA(PC + 2 + shift) - 1 :
										get_ar(v, process, &shift, type);
			if (!nb_arg)
			{
				REG[val[0]] = val[1] ^ val[2];
				if (v->display_mode == 1)
				{
					printf("P%5d | xor %d %d r%d\n", NPRO, val[2], val[1], val[0] + 1);
					print_adv(v, process, octal_shift(process, B_OCT, 4, 3));
				}
				CARRY = REG[val[0]] ? 0 : 1;
			}
		}
	}
	PC = (PC + octal_shift(process, B_OCT, 4, 3)) % MEM_SIZE;
}