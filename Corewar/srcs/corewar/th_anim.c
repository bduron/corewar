/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:25:09 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/21 19:47:29 by pboutelo         ###   ########.fr       */
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
		if (i % 2)
			wattron(a->v->win_champions[a->i], A_BOLD);
		mvwprintw(a->v->win_champions[a->i], 0, 0, "%ls", LIFE_FULL_1);
		mvwprintw(a->v->win_champions[a->i], 1, 0, "%ls", LIFE_FULL_2);
		mvwprintw(a->v->win_champions[a->i], 2, 0, "%ls", LIFE_FULL_3);
		mvwprintw(a->v->win_champions[a->i], 3, 0, "%ls", LIFE_FULL_4);
		mvwprintw(a->v->win_champions[a->i], 4, 0, "%ls", LIFE_FULL_5);
		mvwprintw(a->v->win_champions[a->i], 5, 0, "%ls", LIFE_FULL_6);
		if (i % 2)
			wattroff(a->v->win_champions[a->i], A_BOLD);
		wrefresh(a->v->win_champions[a->i]);
		pthread_mutex_unlock(&a->v->mutex);
		usleep(70000);
	}
	pthread_mutex_lock(&a->v->mutex);
	wrefresh(a->v->win_champions[a->i]);
	a->v->anim_flags ^= 1 << a->i;
	pthread_mutex_unlock(&a->v->mutex);
	free(a);
	pthread_exit(0);
}
