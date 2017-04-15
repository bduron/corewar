/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:25:09 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/15 17:28:29 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_anim_routine(void *p_data)
{
	t_anim		*a;
	// t_viewer		*v;
	int			i;

	a = (t_anim *)p_data;
	i = 10;
	while (i--)
	{
		pthread_mutex_lock(&a->v->mutex);
		werase(a->v->win_champions[a->i]);
		mvwprintw(a->v->win_champions[a->i], 0, 0, "frame %d", i);
		wrefresh(a->v->win_champions[a->i]);
		pthread_mutex_unlock(&a->v->mutex);
		usleep(50000);
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
