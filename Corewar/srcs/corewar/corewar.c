/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/04/13 15:08:40 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int argc, char **argv)
{
	t_vm	v;

	vm_init(&v);
	v.display_mode = (argc == 6 && !ft_strcmp("-n", argv[1])) ? 2 : 1;
	get_players(argc, argv, &v);
	load_arena(&v);
	if (v.display_mode == 2)
	{
		ft_printf("INTERACTIF \n");
		run_game(&v);
	}
	else if (v.display_mode == 1)
	{
		ft_printf("RAW \n");
		print_processes(&v);		// test print
		test_print_v(&v, argc);		// test print
		run_game(&v);
	}
//	get_winner();
//	vm_free();
	return (0);
}
