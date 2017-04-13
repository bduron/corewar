/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/03/28 14:50:33 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int argc, char **argv)
{
	t_vm	v;
	
	vm_init(&v);
	get_players(argc, argv, &v);
	load_arena(&v);		
	print_processes(&v);		// test print
	test_print_v(&v, argc);		// test print
	run_game(&v);
//	get_winner();	
//	vm_free();

	return (0);
}
