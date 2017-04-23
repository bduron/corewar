/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:09:59 by bduron            #+#    #+#             */
/*   Updated: 2017/04/23 18:15:57 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_help()
{
	ft_printf("Usage: ");
	ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	ft_printf("  -v : Verbosity\n  -i : Interactive mode\n");
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
			get_player(argv, i, v);		
 		else if (!ft_strcmp("-n", argv[i]))
		{
			if (i + 1 < argc && (ft_isdigitstr(argv[i + 1]))) 
			{
				if ((c = ft_strstr(argv[i + 2], ".cor")) && c != argv[i + 2] && !c[4]) 
				{
					get_player_custom(argv, i, v);	
					i += 2;
				}
				else 
 					xerror("Error: invalid parameters", -1);
			}
			else 
 				xerror("Error: invalid parameters", -1);
		}	
		else 
 			xerror("Error: invalid parameters", -1);
		i++;	
	}
}	
