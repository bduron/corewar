/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:37:11 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:50:36 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_viewer.h"

void	*th_core_routine(void *p_data)
{
	t_viewer *v;
	int laps;
	int i;
	int counter;

	v = (t_viewer *)p_data;
	laps = 0;
	counter = v->lpf;
	while (1)
	{
		// ----------------------------
		// put the program logic here
		// ...
		// ...
		// ...
		// ----------------------------
		// ----------------------------
		// then render specific frame here
		--counter;
		if (!counter)
		{
			i = -1;
			while (++i < 4)
			{
				bzero(v->events + i, 100);
				sprintf(v->events[i], "%d %s", laps, v->names[i]);
			}
			sem_port_post(&v->sem_coreDone);
			sem_port_wait(&v->sem_ready2core);
			counter = v->lpf;
		}
		// ----------------------------
		++laps;
	}
	pthread_exit(0);
}
