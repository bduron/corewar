/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_shift.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:50:19 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/03 16:07:24 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_arg(size_t arg, size_t n, size_t arg_nb)
{
	size_t n00;
	size_t n01;
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

void	octal_shift(t_list *process, size_t n, size_t label_size, size_t arg_nb)
{
	int shift;

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
	PC += shift;
	PC %= MEM_SIZE;
}
