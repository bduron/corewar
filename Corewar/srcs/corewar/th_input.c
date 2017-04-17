/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:38:00 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/17 19:31:26 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

t_anim	*new_anim(t_viewer *v, int i, const char *str)
{
	t_anim *a;

	if (!(a = (t_anim *)ft_memalloc(sizeof(t_anim))))
		return (NULL);

	a->v = v;
	a->i = i;
	a->type = ft_strdup(str);
	return (a);
}

void	*th_input_routine(void *p_data)
{
	t_viewer	*v;
	int			input;
	t_anim		*a;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	werase(v->win_infos);
	mvwprintw(v->win_infos, 0, 0, "FPS:   %-10d CONTROLS: [ << '%c' ] [ '%c' >> ]", 1048576 / v->fps, KEY_FPS_PP, KEY_FPS_LL);
	mvwprintw(v->win_infos, 1, 0, "LPF:   %-10d CONTROLS: [ << '%c' ] [ '%c' >> ]", v->lpf, KEY_LPF_LL, KEY_LPF_PP);
	mvwprintw(v->win_infos, 2, 0, "PAUSE: %-10s CONTROLS: [ '%c' ]", ONOFF(v->event_flags & FLAG_EVENT_PAUSE), KEY_PAUSE);
	mvwprintw(v->win_infos, 3, 0, "QUIT:             CONTROLS: [ '%c' ]", KEY_QUIT);
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
			else if (input == KEY_PROCESS_LL)
				v->process_offset -= (v->process_offset) ? 1 : 0;
			else if (input == KEY_PROCESS_PP)
				v->process_offset += (v->process_offset + getmaxy(v->win_processes) < v->vm->nprocess) ? 1 : 0;
			else if (input == KEY_PAUSE)
			{
				v->event_flags ^= FLAG_EVENT_PAUSE;
				pthread_cond_broadcast(&v->cond);
			}
			else if ('0' < input && input < '5' && !(v->anim_flags & (1 << (input - '1'))))
			{
				v->anim_flags |= (1 << (input - '1'));
				// printf("555555555555555555555555555555555555555555555555555555555555555555555\n\n");
				a = new_anim(v, input - '1', "test");
				// printf("191919191919191919191919191919191919191919191919191919191919191919191\n\n");
				if (pthread_create(&v->th_anim[input - '1'], NULL, &th_anim_routine, a) < 0) {
					fprintf(stderr, "pthread_create error for th_anim[%d]\n", input - '1');
					exit(1);
				}
			}
			mvwprintw(v->win_infos, 0, 7, "%-10d", 1048576 / v->fps);
			mvwprintw(v->win_infos, 1, 7, "%-10d", v->lpf);
			mvwprintw(v->win_infos, 2, 7, "%-10s", ONOFF(v->event_flags & FLAG_EVENT_PAUSE));
			wrefresh(v->win_infos);

			maj_process(v); // que si on a appuyé sur les touches "i" ou "j" !!!
			pthread_mutex_unlock(&v->mutex);
		}
	}
	pthread_exit(0);
}
