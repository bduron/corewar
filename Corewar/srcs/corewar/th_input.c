/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:38:00 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/13 16:20:51 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_input_routine(void *p_data)
{
	t_viewer	*v;
	int			input;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	werase(v->win_infos);
	mvwprintw(v->win_infos, 0, 0, "FPS: %d\t\t\tCONTROLS: [ << '%c' ] [ '%c' >> ]", 1048576 / v->fps, KEY_FPS_PP, KEY_FPS_LL);
	mvwprintw(v->win_infos, 1, 0, "LPF: %d\t\t\tCONTROLS: [ << '%c' ] [ '%c' >> ]", v->lpf, KEY_LPF_LL, KEY_LPF_PP);
	mvwprintw(v->win_infos, 2, 0, "PAUSE: %s\t\tCONTROLS: [ '%c' ]", ONOFF(v->event_flags & FLAG_EVENT_PAUSE), KEY_PAUSE);
	mvwprintw(v->win_infos, 3, 0, "QUIT:\t\t\tCONTROLS: [ '%c' ]", KEY_QUIT);
	wrefresh(v->win_infos);
	pthread_mutex_unlock(&v->mutex);
	while(1)
	{
		// printf("INPUT");
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
			else if (input == KEY_PAUSE)
			{
				v->event_flags ^= FLAG_EVENT_PAUSE;
				pthread_cond_broadcast(&v->cond);
			}
			werase(v->win_infos);
			mvwprintw(v->win_infos, 0, 0, "FPS: %d\t\t\tCONTROLS: [ << '%c' ] [ '%c' >> ]", 1048576 / v->fps, KEY_FPS_PP, KEY_FPS_LL);
			mvwprintw(v->win_infos, 1, 0, "LPF: %d\t\t\tCONTROLS: [ << '%c' ] [ '%c' >> ]", v->lpf, KEY_LPF_LL, KEY_LPF_PP);
			mvwprintw(v->win_infos, 2, 0, "PAUSE: %s\t\tCONTROLS: [ '%c' ]", ONOFF(v->event_flags & FLAG_EVENT_PAUSE), KEY_PAUSE);
			mvwprintw(v->win_infos, 3, 0, "QUIT:\t\t\tCONTROLS: [ '%c' ]", KEY_QUIT);
			wrefresh(v->win_infos);
			pthread_mutex_unlock(&v->mutex);
		}
	}
	pthread_exit(0);
}
