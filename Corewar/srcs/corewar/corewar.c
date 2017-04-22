/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/04/22 12:52:44 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_help()
{
	ft_printf("This is help\n");
	exit(0);
}

void	parse_opt(int argc, char **argv, t_vm *v)
{
	int i;
	char *c;

	i = 1;
	while (i < argc)
	{
 		if (!ft_strcmp("-i", argv[i]))
 			v->opt_flags |= FLAG_OPT_NCURSES;
 		else if (!ft_strcmp("-v", argv[i]))
 			v->opt_flags |= FLAG_OPT_VERBOSE;
 		else if (!ft_strcmp("-dump", argv[i]))
 		{
 			v->opt_flags |= FLAG_OPT_DUMP;
			if (i + 1 < argc && ft_isdigit(*argv[i + 1])) 
 				v->dump_param = ft_atoi(argv[++i]);
			else 
 				xerror("Error: invalid dump parameter", -1);
 		}
		else if ((c = ft_strstr(argv[i], ".cor")) && c != argv[i] && !c[4])
		{		
 			if (is_valid_player(argv[i]))
			{
				if (v->nplayer < 4)
					save_player(argv[i], v, v->nplayer);
				else
 					xerror("Error: too many players", -1);
				v->nplayer++;
			}
 			else
 				xerror("Error: invalid champion", -1);
		}
		else 
 			xerror("Error: invalid parameters", -1);
		i++;	
	}
}	

// [x] dump [dump + int obligatoire]
// [x] visu 
// [ ] players + num 
// [x] verbosity
// [ ] help


int			main(int argc, char **argv)
{
	t_vm		vm;
	t_viewer	v;

	if (argc == 1)
	   print_help();	

	vm_init(&vm);
	parse_opt(argc, argv, &vm);
	/***/
	vm.display_mode = (vm.opt_flags & FLAG_OPT_NCURSES) ? 2 : 3;
	vm.display_mode = (vm.opt_flags & FLAG_OPT_VERBOSE) ? 1 : 3;
	/***/
//	get_players(argc, argv, &vm);
	load_arena(&vm);
	if (vm.display_mode == 2)
	{
		viewer_init(&v, &vm);
		viewer_run(&v);
	}
	else //if (vm.display_mode == 1)
	{
//		print_processes(&vm);		// test print
//		test_print_v(&vm, argc);		// test print
		run_game(&vm);
	}
//	get_winner();
//	vm_free();
	return (0);
}

