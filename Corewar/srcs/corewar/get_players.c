
#include "corewar.h"

void is_player(t_vm *v, int live)
{
	int i;

	i = -1;
	while (++i < v->nplayer)
		if (live == v->p[i].nplayer)
		{
			if (v->display_mode == 1)
				printf("Player %d (%s) is said to be alive\n", i + 1, v->p[i].name);
			else if (v->display_mode == 2 && !(v->v->anim_flags & (1 << i)))
				heal(v->v, i);
			v->p[i].nblive++;
			v->p[i].last_live_cycle = v->ncycle;
			v->last_live_id = i;
		}
}

void save_player(char *file, t_vm *v, int i)
{
	int	fd;
	int len;

	if ((fd = open(file, O_RDONLY)) != -1)
	{
		read(fd, &(v->p[i].exec_magic), sizeof(int));
		read(fd, &(v->p[i].name), PROG_NAME_LENGTH);
		lseek(fd, 8, SEEK_CUR); // ZAZ tweak skip prog len
		read(fd, &(v->p[i].comment), COMMENT_LENGTH);
		lseek(fd, 4, SEEK_CUR); // ZAZ tweak skip
		len = read(fd, &(v->p[i].code), CHAMP_MAX_SIZE);
		v->p[i].nplayer = (i + 1) * -1;
		v->p[i].prog_len = len;
		v->p[i].nblive = 0;
		v->p[i].last_live_cycle = 0;
	}
	else
		xerror("Error: cannot open file", -1);
	close(fd);
}

void get_players(int argc, char **argv, t_vm *v)
{
	int i;

	if (argc > MAX_PLAYERS + v->display_mode)
		xerror("Error: too many champions", -1);
	i = v->display_mode;
	while (i < argc)
	{
		if (is_valid_player(argv[i]))
			save_player(argv[i], v, i - v->display_mode);
		else
			xerror("Error: invalid champion", -1);
		i++;
	}
	v->nplayer = argc - v->display_mode;
}
