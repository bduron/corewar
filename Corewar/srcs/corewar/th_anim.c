/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:25:09 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/20 08:24:53 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_anim_routine(void *p_data)
{
	t_anim		*a;
	int			i;

	a = (t_anim *)p_data;
	i = 8;
	while (i--)
	{
		pthread_mutex_lock(&a->v->mutex);
		werase(a->v->win_champions[a->i]);
		// mvwprintw(a->v->win_champions[a->i], 0, 0, "frame %d", i);
		if (i % 2)
			wattron(a->v->win_champions[a->i], A_BOLD);
		// mvwprintw(a->v->win_champions[a->i], 0, 0, a->type, i);
		mvwprintw(a->v->win_champions[a->i], 0, 0, " _ _");
		mvwprintw(a->v->win_champions[a->i], 1, 0, "| ' |");
		mvwprintw(a->v->win_champions[a->i], 2, 0, " \\ /");
		if (i % 2)
			wattroff(a->v->win_champions[a->i], A_BOLD);

		mvwprintw(a->v->win_champions[a->i], 3, 0, MSG_LIFE);
		wattron(a->v->win_champions[a->i], A_BOLD);
		mvwprintw(a->v->win_champions[a->i], 3, (8 - i) / 2, "%c", MSG_LIFE[(8 - i) / 2]);
		wattroff(a->v->win_champions[a->i], A_BOLD);


		wrefresh(a->v->win_champions[a->i]);
		pthread_mutex_unlock(&a->v->mutex);
		usleep(70000);
		// usleep(100000 * i);
	}
	pthread_mutex_lock(&a->v->mutex);
	werase(a->v->win_champions[a->i]);
	wrefresh(a->v->win_champions[a->i]);
	a->v->anim_flags ^= 1 << a->i;
	pthread_mutex_unlock(&a->v->mutex);
	free(a->type);
	free(a);
	pthread_exit(0);
}
