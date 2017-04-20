/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:37:11 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/20 12:37:09 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_core_routine(void *p_data)
{
	t_viewer	*v;
	int			laps;
	int			cooldown;
	// int			offset = 4365;

	v = (t_viewer *)p_data;
	laps = 0;
	pthread_mutex_lock(&v->mutex);
	while (1)
	{
		// printf("CORE");
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
			// while (v->process_lst != NULL)
			// {
			// 	printf("It is now cycle %d\n", v->ncycle); // DEBUG
			// 	update_vm(v);
			// 	browse_processes_lst(v);
			// 	if (v->cycle_to_die < 0)
			// 		break;
			// }

			// while ((cooldown || offset) && v->vm->process_lst)
			while (cooldown && v->vm->process_lst)
			{
				/* ... */
				// v->vm->ncycle++;
				update_vm(v->vm);
				browse_processes_lst(v->vm);
				if (v->vm->cycle_to_die < 0)
					break ;
				++laps;
				--cooldown;
				// --offset;
			}
			/* ... */
			pthread_mutex_lock(&v->mutex);
			v->event_flags |= FLAG_EVENT_CORE;
			pthread_cond_broadcast(&v->cond);
		}
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
