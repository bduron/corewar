/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 13:55:14 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/18 16:44:28 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	get_ar(t_vm *v, t_list *process, u_char *shift, u_char type)
{
	int		ret;
	u_char	label;

	label = type >> 2 ? 2 : 4;
	if ((type & 0b11) == 1)
		ret = REG[ARENA(PC + 2 + (*shift)++) - 1];
	else if ((type & 0b11) == 2)
	{
		ret = reverse_bytes(&ARENA(PC + 2 + *shift), label);
		*shift += label;
	}
	else
	{
		ret = reverse_bytes(&ARENA(PC + 2 + *shift), 2) % IDX_MOD;
		ret = reverse_bytes(&ARENA(PC + ret), 4);
		ret = type >> 2 ? ret % IDX_MOD : ret;
		*shift += 2;
	}
	return (ret);
}

int reverse_bytes(unsigned char *addr, int nbytes)
{
	unsigned char two_bytes[2];
	unsigned char four_bytes[4];

	if (nbytes == 2)
	{
		two_bytes[0] = *(unsigned char *)(addr + 1);
		two_bytes[1] = *(unsigned char *)(addr);
		return (*(short *)&two_bytes[0]);
	}
	if (nbytes == 4)
	{
		four_bytes[0] = *(unsigned char *)(addr + 3);
		four_bytes[1] = *(unsigned char *)(addr + 2);
		four_bytes[2] = *(unsigned char *)(addr + 1);
		four_bytes[3] = *(unsigned char *)(addr);
		return (*(int *)&four_bytes[0]);
	}
	return (-1);
}

void	execute_op(t_vm *v, t_list *process)
{
	if (v->display_mode == 1)
		printf("EXECUTION : %s\n", op_tab[NEXT_OP].name);
	op_tab[NEXT_OP].f(v, process);
}

void	init_next_op(t_vm *v, t_list *process)
{
	if (ARENA(PC) > 16 || !ARENA(PC))
	{
		NEXT_OP = -1;
		PC++;
		if (v->display_mode == 1)
			printf("FAIL !\n");
	}
	else
	{
		NEXT_OP = ARENA(PC) - 1;
		OP_CAST = op_tab[NEXT_OP].cycle - 1; // arbitraire pour le moment
		if (v->display_mode == 1)
		{
			printf("numero d'op : %2x\t", ARENA(PC));
			printf("cast moi ce spell noob : %2d\n", OP_CAST);
		}
	}
}

void	operate_process(t_vm *v, t_list *process)
{
	if (NEXT_OP >= 0 && NEXT_OP < 16)
		execute_op(v, process);
	init_next_op(v, process);
}
