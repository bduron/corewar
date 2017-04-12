/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:46:21 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_viewer.h"

void	*th_render_routine(void *p_data)
{
	t_viewer *v;
	int i;

	v = (t_viewer *)p_data;

	while(v->input != 'q' && v->input != 'Q')
	{
		sem_port_wait(&v->sem_coreDone);
		sem_port_wait(&v->sem_sleepDone);
		if (v->flag_pause)
			sem_port_wait(&v->sem_pause);
		i = -1;
		while (++i < 4)
		{
			werase(v->win_champions[i]);
			mvwprintw(v->win_champions[i], 0, 0, v->events[i]);
			wrefresh(v->win_champions[i]);
		}
		sem_port_post(&v->sem_ready2core);
		sem_port_post(&v->sem_ready2sleep);
	}
	pthread_exit(0);
}
