/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/04/19 15:37:29 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int argc, char **argv)
{
	t_vm		vm;
	t_viewer	v;

	vm_init(&vm);
	// vm.display_mode = (argc == 6 && !ft_strcmp("-n", argv[1])) ? 2 : 1;
	vm.display_mode = (!ft_strcmp("-n", argv[1])) ? 2 : 1;
	get_players(argc, argv, &vm);
	load_arena(&vm);
	if (vm.display_mode == 2)
	{
		viewer_init(&v, &vm);
		viewer_run(&v);
	}
	else if (vm.display_mode == 1)
	{
		print_processes(&vm);		// test print
		test_print_v(&vm, argc);		// test print
		run_game(&vm);
	}
//	get_winner();
//	vm_free();
	return (0);
}
