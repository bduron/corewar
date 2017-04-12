/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:38:00 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:46:47 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_viewer.h"

void	*th_input_routine(void *p_data)
{
	t_viewer	*v;

	v = (t_viewer *)p_data;
	werase(v->win_infos);
	mvwprintw(v->win_infos, 2, 3, "actual display time is %d usec.\t\t(edit width %c & %c)", v->fps, FPS_LL, FPS_PP);
	mvwprintw(v->win_infos, 3, 3, "recording one frame every %d laps.\t\t(edit width %c & %c)", v->lpf, LPF_LL, LPF_PP);
	mvwprintw(v->win_infos, 4, 3, "Press 'q' to quit");
	wrefresh(v->win_infos);
	while(v->input != 'q' && v->input != 'Q')
	{
		if ((v->input = getch()) == ERR)
		{
			// stop_curses(&cinfo);
			// fprintf(stderr, "ERR returned from getch()\n");
			// pthread_exit(0);
		}
		else if (v->input == FPS_LL)
			v->fps /= (v->fps > 4096) ? 2 : 1;
		else if (v->input == FPS_PP)
			v->fps *= (v->fps < 1048576) ? 2 : 1;
		else if (v->input == LPF_LL)
			v->lpf /= (v->lpf > 1) ? 2 : 1;
		else if (v->input == LPF_PP)
			v->lpf *= (v->lpf < 1000) ? 2 : 1;
		else if (v->input == ' ')
		{
			if (!(v->flag_pause = !v->flag_pause))
				sem_port_post(&v->sem_pause);
		}
		else if (v->input == 'q')
			break ;
		werase(v->win_infos);
		mvwprintw(v->win_infos, 2, 3, "actual display time is %d usec.\t\t(edit width %c & %c)", v->fps, FPS_LL, FPS_PP);
		mvwprintw(v->win_infos, 3, 3, "recording one frame every %d laps.\t\t(edit width %c & %c)", v->lpf, LPF_LL, LPF_PP);
		mvwprintw(v->win_infos, 4, 3, "Press 'q' to quit");
		mvwprintw(v->win_infos, 5, 3, v->flag_pause ? "PAUSE" : "");
		wrefresh(v->win_infos);
	}
	pthread_exit(0);
}
