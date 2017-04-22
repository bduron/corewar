/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/04/22 10:33:45 by pboutelo         ###   ########.fr       */
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
//		print_processes(&vm);		// test print
//		test_print_v(&vm, argc);		// test print
		run_game(&vm);
	}
//	get_winner();
//	vm_free();
	return (0);
}
//
// # define FLAG_OPT_VERBOSE 1
// # define FLAG_OPT_VERBOSE_LIVES 1
// # define FLAG_OPT_VERBOSE_CYCLES 1
// # define FLAG_OPT_VERBOSE_OPERATIONS 1
// # define FLAG_OPT_DUMP 2
// # define FLAG_OPT_NCURSES 4
//
// int			main(int argc, char **argv)
// {
// 	t_vm		vm;
// 	t_viewer	v;
// 	int i;
//
// 	vm_init(&vm);
// 	vm.option_flags = 0;
// 	// vm.display_mode = (argc == 6 && !ft_strcmp("-n", argv[1])) ? 2 : 1;
// 	i = 0;
// 	while (++i < argc)
// 	{
// 		if (!ft_strcmp("-n", argv[i]))
// 			vm.option_flags |= FLAG_OPT_NCURSES;
// 		else if (!ft_strcmp("-v", argv[i]))
// 			vm.option_flags |= FLAG_OPT_VERBOSE;
// 		else if (!ft_strcmp("-dump", argv[i]))
// 		{
// 			vm.option_flags |= FLAG_OPT_DUMP;
// 			vm.dump_param = ft_atoi(argv[++i]);
// 		}
// 		else if (!ft_strcmp(".cor", argv[i] + ft_strlen(argv[i]) - (ft_strlen(argv[i]) < 4 ? ft_strlen(argv[i]) : 4)))
// 		{
// 			if (is_valid_player(argv[i]))
// 				save_player(argv[i], v, i - v->display_mode);
// 			else
// 				xerror("Error: invalid champion", -1);
// 		}
// 	}
// 	vm.display_mode = (!ft_strcmp("-n", argv[1])) ? 2 : 1;
// 	get_players(argc, argv, &vm);
// 	load_arena(&vm);
// 	if (vm.display_mode == 2)
// 	{
// 		viewer_init(&v, &vm);
// 		viewer_run(&v);
// 	}
// 	else if (vm.display_mode == 1)
// 	{
// //		print_processes(&vm);		// test print
// //		test_print_v(&vm, argc);		// test print
// 		run_game(&vm);
// 	}
// //	get_winner();
// //	vm_free();
// 	return (0);
// }
