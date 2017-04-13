/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:37:11 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/13 11:52:38 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_viewer.h"

void	*th_core_routine(void *p_data)
{
	t_viewer	*v;
	int			i;
	int			laps;
	int			cooldown;

	v = (t_viewer *)p_data;
	laps = 0;
	pthread_mutex_lock(&v->mutex);
	while (1)
	{
		if (v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		if (v->event_flags & FLAG_EVENT_CORE)
			pthread_cond_wait(&v->cond, &v->mutex);
		else
		{
			cooldown = v->lpf;
			pthread_mutex_unlock(&v->mutex);
			/* next code will be executed in parallel with other threads */
			while (cooldown)
			{
				/* ... */
				++laps;
				--cooldown;
			}
			/* ... */
			pthread_mutex_lock(&v->mutex);
			i = -1;
			while (++i < 4)
			{
				bzero(v->events + i, 100);
				sprintf(v->events[i], "%d %s", laps, v->names[i]);
			}
			v->event_flags |= FLAG_EVENT_CORE;
			pthread_cond_broadcast(&v->cond);
		}
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
