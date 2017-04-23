/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:59:06 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/23 12:23:32 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void is_player(t_vm *v, int live)
{
	int i;

	i = -1;
	while (++i < v->nplayer)
		if (live == v->p[i].nplayer)
		{
			if (v->display_mode == 1)
				ft_printf("Player %d (%s) is said to be alive\n", i + 1, v->p[i].name);
			else if (v->display_mode == 2)
			{
				pthread_mutex_lock(&v->v->mutex);
				if (!(v->v->heal_flag[i] || v->v->credits_flag))
					heal(v->v, i);
				pthread_mutex_unlock(&v->v->mutex);
			}
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

void get_player(char **argv, int i, t_vm *v)
{
 			if (is_valid_player(argv[i]))
			{
				if (v->nplayer < MAX_PLAYERS)
					save_player(argv[i], v, v->nplayer);
				else
 					xerror("Error: too many players", -1);
				v->nplayer++;
			}
 			else
 				xerror("Error: invalid champion", -1);
}
