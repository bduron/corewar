/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/13 14:29:39 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;
	int			i;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	while(1)
	{
		if (v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		if ((v->event_flags & FLAG_EVENT_CORE)
			&& (v->event_flags & FLAG_EVENT_TIMER)
			&& !(v->event_flags & FLAG_EVENT_PAUSE))
		{
			i = -1;
			while (++i < 4)
			{
				werase(v->win_champions[i]);
				mvwprintw(v->win_champions[i], 0, 0, v->events[i]);
				wrefresh(v->win_champions[i]);
			}
			v->event_flags ^= (FLAG_EVENT_CORE | FLAG_EVENT_TIMER);
			pthread_cond_broadcast(&v->cond);
		}
		else
			pthread_cond_wait(&v->cond, &v->mutex);
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
