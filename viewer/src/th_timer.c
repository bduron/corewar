/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_timer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:39:05 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:45:48 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_viewer.h"

void	*th_timer_routine(void *p_data)
{
	t_viewer	*v;
	int			i;

	v = (t_viewer *)p_data;
	i = 0;
	while(v->input != 'q' && v->input != 'Q')
	{
		sem_port_wait(&v->sem_ready2sleep);
		usleep(v->fps);
		werase(v->win_arena);
		mvwprintw(v->win_arena, 2, 3, "%d", i++);
		wrefresh(v->win_arena);
		sem_port_post(&v->sem_sleepDone);
	}
	pthread_exit(0);
}
