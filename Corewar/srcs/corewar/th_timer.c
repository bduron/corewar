/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_timer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:39:05 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/13 16:20:42 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_timer_routine(void *p_data)
{
	t_viewer	*v;
	int			i;

	v = (t_viewer *)p_data;
	i = 0;
	pthread_mutex_lock(&v->mutex);
	while(1)
	{
		// printf("TIMER");
		if (v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		if (v->event_flags & FLAG_EVENT_TIMER)
			pthread_cond_wait(&v->cond, &v->mutex);
		else
		{
			pthread_mutex_unlock(&v->mutex);
			/* next code will be executed in parallel with other threads */
			usleep(v->fps);
			/* ... */
			pthread_mutex_lock(&v->mutex);
			v->event_flags |= FLAG_EVENT_TIMER;
			pthread_cond_broadcast(&v->cond);
		}
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
