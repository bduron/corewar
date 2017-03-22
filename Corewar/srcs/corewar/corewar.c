/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/03/22 15:33:25 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int argc, char **argv)
{
	t_vm	v;
	
	vm_init(&v);
	get_players(argc, argv, &v);
	load_arena(&v);		
	print_processes(&v);
//	test_print_v(&v, argc); //test
//	run_game();
//	get_winner();	
//	vm_free();

	return (0);
}
