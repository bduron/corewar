/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_shift.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:50:19 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/20 18:23:21 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_reg(t_vm *v, t_list *process, unsigned int val, int addr)
{
	char i;
	
	i = 4;
	while (i--)
	{
		OWNER(addr) = OWNER(PC);
		ARENA(addr--) = val & 0xFF;
		val >>= 8;
	}
}

int		check_arg(u_char arg, u_char n, u_char arg_nb)
{
	u_char n00;
	u_char n01;
	int shift;
	int k;

	k = 0;
	shift = 6;
	while (k < 4)
	{
		n01 = (n >> shift) & 0b11;
		n00 = n01 ? 1 << (n01 - 1) : 0;
		if (arg_nb > 0 && !(n00 & op_tab[arg].args[k]))
			return (0);
		else if (n00 && arg_nb <= 0)
			return (0);
		arg_nb -= arg_nb ? 1 : 0;
		k++;
		shift -= 2;
	}
	return (1);
}

int		octal_shift(t_list *process, u_char n, u_char label_size, u_char arg_nb)
{
	int shift;

	(void)process; //SADNESS
	shift = 2;
	while (++arg_nb <= 4)
		n >>= 2;
	while (n)
	{
		shift += ((n & 0b11) == 0b01) ? 1 : 0;
		shift += ((n & 0b11) == 0b11) ? 2 : 0;
		shift += ((n & 0b11) == 0b10) ? label_size : 0;
		n >>= 2;
	}
	return (shift);
}
