/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_th_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 11:03:16 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	update_anim(t_viewer *v, int i, char state) // TODO fusionner avec maj_lifes
{
	if (state != v->anim_state[i] && state < v->anim_state[i])
	{
		v->anim_state[i] = state;
		werase(v->win_champions[i]);
		wattron(v->win_champions[i], COLOR_PAIR(i + 2));
		if (state == LIFE_DEAD)
			draw_life_dead(v, i);
		else if (state == LIFE_LOW)
			draw_life_low(v, i);
		else if (state == LIFE_MEDIUM)
			draw_life_medium(v, i);
		else if (state == LIFE_HIGH)
			draw_life_high(v, i);
		else if (state == LIFE_FULL)
			draw_life_full(v, i);
		wattroff(v->win_champions[i], COLOR_PAIR(i + 2));
		wrefresh(v->win_champions[i]);
	}
}

void	maj_lifes(t_viewer *v)
{
	int i;
	int state;

	i = -1;
	while (++i < v->vm->nplayer)
	{
		if (!(v->anim_flags & (1 << i))
			&& v->vm->p[i].last_live_cycle <= (v->vm->ncycle - v->vm->ncycle_mod))
		{
			state = 100 * (v->vm->cycle_to_die - v->vm->ncycle_mod) / v->vm->cycle_to_die;
			if (state < LIFE_LOW)
				update_anim(v, i, LIFE_LOW);
			else if (state < LIFE_MEDIUM)
				update_anim(v, i, LIFE_MEDIUM);
			else if (state < LIFE_HIGH)
				update_anim(v, i, LIFE_HIGH);
			else
				update_anim(v, i, LIFE_FULL);
		}
	}
}

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	init_arena(v);
	init_register(v);
	maj_process(v);
	maj_lifes(v);
	while(1)
	{
		if (v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		if ((v->event_flags & FLAG_EVENT_CORE)
			&& (v->event_flags & FLAG_EVENT_TIMER)
			&& !(v->event_flags & FLAG_EVENT_PAUSE))
		{
			maj_lifes(v);
			maj_arena(v);
			maj_process(v);
			mvwprintw(v->win_infos, 0, 69, "%-10d", v->vm->ncycle);
			mvwprintw(v->win_infos, 1, 69, "%-10d", v->vm->ncycle_mod);
			mvwprintw(v->win_infos, 2, 69, "%-10d", v->vm->cycle_to_die);
			wrefresh(v->win_infos);
			v->event_flags ^= (FLAG_EVENT_CORE | FLAG_EVENT_TIMER);
			pthread_cond_broadcast(&v->cond);
		}
		else
			pthread_cond_wait(&v->cond, &v->mutex);
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
