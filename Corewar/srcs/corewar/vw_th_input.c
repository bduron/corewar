/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_th_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:38:00 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 11:04:11 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*th_input_routine(void *p_data)
{
	t_viewer	*v;
	int			input;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	init_win_infos(v);
	pthread_mutex_unlock(&v->mutex);
	while(1)
	{
		if (((input = getch()) == ERR)
			|| input == KEY_QUIT)
		{
			pthread_mutex_lock(&v->mutex);
			v->event_flags |= FLAG_EVENT_QUIT;
			pthread_cond_broadcast(&v->cond);
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		else
		{
			pthread_mutex_lock(&v->mutex);
			if (input == KEY_FPS_LL)
				v->fps /= (v->fps > 4096) ? 2 : 1;
			else if (input == KEY_FPS_PP)
				v->fps *= (v->fps < 1048576) ? 2 : 1;
			else if (input == KEY_LPF_LL)
				v->lpf /= (v->lpf > 1) ? 2 : 1;
			else if (input == KEY_LPF_PP)
				v->lpf *= (v->lpf < 1000) ? 2 : 1;
			else if (input == KEY_PROCESS_LL)
			{
				if (v->process_selected)
					--v->process_selected;
				if (v->process_selected < v->process_offset)
					--v->process_offset;
			}
			else if (input == KEY_PROCESS_PP)
			{
				if (v->process_selected != v->vm->nprocess - 1)
					++v->process_selected;
				if (v->process_offset + getmaxy(v->win_processes) - 1 < v->process_selected)
					++v->process_offset;
			}
			else if (input == KEY_PAUSE)
			{
				v->event_flags ^= FLAG_EVENT_PAUSE;
				pthread_cond_broadcast(&v->cond);
			}
			maj_win_infos(v);
			maj_process(v); // que si on a appuyé sur les touches "i" ou "j" !!!
			pthread_mutex_unlock(&v->mutex);
		}
	}
	pthread_exit(0);
}
