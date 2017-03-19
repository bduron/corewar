
#include "corewar.h"

void save_player(char *file, t_vm *v, int i)
{
	int	fd;
	int len;
	 	
	i = i - 1;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		read(fd, &(v->p[i].exec_magic), sizeof(int));
		read(fd, &(v->p[i].name), PROG_NAME_LENGTH);
		lseek(fd, 8, SEEK_CUR); // ZAZ tweak skip prog len
		read(fd, &(v->p[i].comment), COMMENT_LENGTH);
		lseek(fd, 4, SEEK_CUR); // ZAZ tweak skip 
		len = read(fd, &(v->p[i].code), CHAMP_MAX_SIZE);
		v->p[i].nplayer = i + 1;
		v->p[i].prog_len = len;
	}
	else 
		xerror("Error: cannot open file", -1);
	close(fd);
} 

void get_players(int argc, char **argv, t_vm *v)
{
	int i;

	if (argc > MAX_PLAYERS + 1) 
		xerror("Error: too many champions", -1);
	i = 1;	
	while (i < argc)
	{
		if (is_valid_player(argv[i]))
			save_player(argv[i], v, i);
		else 
			xerror("Error: invalid champion", -1);
		i++;
	}
}
