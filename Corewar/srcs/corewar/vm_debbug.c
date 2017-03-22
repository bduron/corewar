#include "corewar.h"
# define RES "\x1B[0m"

void print_processes(t_vm *v)
{
	t_list *tmp;
	int i;

	tmp = v->process_lst;
	i = 0;			
	while (tmp)	
	{
		ft_printf("\n======= %d =======\n", i);		
		ft_printf("|_carry:        %d\n", ((t_process *)v->process_lst->content)->carry);
		ft_printf("|_pc:           %d\n", ((t_process *)v->process_lst->content)->pc);
		ft_printf("|_live count:   %d\n", ((t_process *)v->process_lst->content)->live_count);
		ft_printf("|_op cast:      %d\n", ((t_process *)v->process_lst->content)->op_cast);
		ft_printf(" _______________________________________________________________\n");
		ft_printf("| r1| r2| r3| r4| r5| r6| r7| r8| r9|r10|r11|r12|r13|r14|r15|r16|\n");
		ft_printf("|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|% 3d|\n\n", 
			((t_process *)v->process_lst->content)->reg[0],
			((t_process *)v->process_lst->content)->reg[1],
			((t_process *)v->process_lst->content)->reg[2],
			((t_process *)v->process_lst->content)->reg[3],
			((t_process *)v->process_lst->content)->reg[4],
			((t_process *)v->process_lst->content)->reg[5],
			((t_process *)v->process_lst->content)->reg[6],
			((t_process *)v->process_lst->content)->reg[7],
			((t_process *)v->process_lst->content)->reg[8],
			((t_process *)v->process_lst->content)->reg[9],
			((t_process *)v->process_lst->content)->reg[10],
			((t_process *)v->process_lst->content)->reg[11],
			((t_process *)v->process_lst->content)->reg[12],
			((t_process *)v->process_lst->content)->reg[13],
			((t_process *)v->process_lst->content)->reg[14],
			((t_process *)v->process_lst->content)->reg[15],
			((t_process *)v->process_lst->content)->reg[16]);
		tmp = tmp->next;
		i++;
	}
}

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
