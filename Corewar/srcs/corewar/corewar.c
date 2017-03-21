/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/03/21 18:10:31 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
# define RES "\x1B[0m"

void dump(t_player p) // N'affiche pas le dernier octet 0a :s
{
	int j;
	int k; 
	int c;

	j = 0;
	while (j <= p.prog_len)
	{	
		(j == p.prog_len) ? ft_printf("%*c", (((16 - j % 16) * 5) / 2), ' ') : 0;
		if (j % 16 == 0 || p.prog_len == j) 
		{
			ft_printf("  ");	
			k = (p.prog_len == j) ? j - j % 16 : j - 16;
			while (k < j && j != 0)
			{
				c = p.code[k++];
				ft_isprint(c) ? ft_printf("%c", c): ft_printf(".");
			}
			ft_printf("\n");
		}
		if (j % 2 == 0)
			ft_printf(" ");
		if (j < p.prog_len)
			ft_printf("%02x", (p.code[j]));
		j++;
	}
}

void print_arena(t_vm *v)
{
	
	for (int i = 0; i < MEM_SIZE; i++)	
	{
		if (i % 64 == 0)
			ft_printf("\n");
		if (i % 1 == 0) //
			ft_printf(" "); //
		if (v->a.owner[i] == -1)
			ft_printf("%02x", v->a.arena[i]);	
		else 
			ft_printf("\033[%dm%02x" RES, 31 + v->a.owner[i], v->a.arena[i]);	

	}
}

void test_print_v(t_vm *v, int argc)
{

	ft_printf("\n[Nb players = %d]\n\n", v->nplayer);
	for (int i = 0; i < argc - 1; i++)
	{
		ft_printf("nplayer = %d\n", v->p[i].nplayer);
		ft_printf("name = %s\n", v->p[i].name);
		ft_printf("comment = %s\n", (v->p[i].comment));
		dump(v->p[i]);
		ft_printf("\n\n\n");
	}
	print_arena(v);
	

}

int			main(int argc, char **argv)
{
	t_vm	v;
	
	vm_init(&v);
	get_players(argc, argv, &v);
	load_arena(&v);		
	test_print_v(&v, argc); //test
//	run_game();
//	get_winner();	
//	vm_free();

	return (0);
}
