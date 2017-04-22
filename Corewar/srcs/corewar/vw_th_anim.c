/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_th_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:25:09 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 11:03:06 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*th_anim_routine(void *p_data)
{
	t_anim		*a;
	int			i;

	a = (t_anim *)p_data;
	i = 8;
	pthread_mutex_lock(&a->v->mutex);
	werase(a->v->win_champions[a->i]);
	wattron(a->v->win_champions[a->i], COLOR_PAIR(a->i + 2));
	pthread_mutex_unlock(&a->v->mutex);
	while (i--)
	{
		pthread_mutex_lock(&a->v->mutex);
		if (i % 2)
			wattron(a->v->win_champions[a->i], A_BOLD);
		else
			wattroff(a->v->win_champions[a->i], A_BOLD);
		draw_life_full(a->v, a->i);
		wrefresh(a->v->win_champions[a->i]);
		pthread_mutex_unlock(&a->v->mutex);
		usleep(70000);
	}
	pthread_mutex_lock(&a->v->mutex);
	wattroff(a->v->win_champions[a->i], A_BOLD); // Verifier si necessaire
	wattroff(a->v->win_champions[i], COLOR_PAIR(a->i + 2));
	a->v->anim_flags ^= 1 << a->i;
	pthread_mutex_unlock(&a->v->mutex);
	free(a);
	pthread_exit(0);
}
