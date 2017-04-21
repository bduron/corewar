/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:37:11 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/21 19:26:59 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_core_routine(void *p_data)
{
	t_viewer	*v;
	int			cooldown;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	while (1)
	{
		if (v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		if (v->event_flags & FLAG_EVENT_CORE
			|| v->event_flags & FLAG_EVENT_PAUSE)
			pthread_cond_wait(&v->cond, &v->mutex);
		else
		{
			cooldown = v->lpf;
			pthread_mutex_unlock(&v->mutex);
			while (cooldown && v->vm->process_lst)
			{
				update_vm(v->vm);
				if (v->vm->process_lst)
				{
					init_processes_lst(v->vm);
					browse_processes_lst(v->vm);
				}
				--cooldown;
			}
			pthread_mutex_lock(&v->mutex);
			v->event_flags |= FLAG_EVENT_CORE;
			pthread_cond_broadcast(&v->cond);
		}
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
