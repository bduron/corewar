/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:25:09 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/21 18:03:42 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	draw_life(t_viewer *v, int i, char state)
{
	werase(v->win_champions[i]);
	if (state == 100)
	{
		mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_1_100);
		mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_2_100);
		mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_3_100);
		mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_4_100);
		mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_5_100);
		mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_6_100);
		v->anim_flags[i] &= ~FLAG_ANIM_100;
	}
	else if (state == 75)
	{
		mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_1_75);
		mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_2_75);
		mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_3_75);
		mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_4_75);
		mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_5_75);
		mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_6_75);
		v->anim_flags[i] &= ~FLAG_ANIM_75;
	}
	else if (state == 50)
	{
		mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_1_50);
		mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_2_50);
		mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_3_50);
		mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_4_50);
		mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_5_50);
		mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_6_50);
		v->anim_flags[i] &= ~FLAG_ANIM_50;
	}
	else if (state == 25)
	{
		mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_1_25);
		mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_2_25);
		mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_3_25);
		mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_4_25);
		mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_5_25);
		mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_6_25);
		v->anim_flags[i] &= ~FLAG_ANIM_25;
	}
	else if (state == 0)
	{
		mvwprintw(v->win_champions[i], 0, 0, "%ls", SKULL_1);
		mvwprintw(v->win_champions[i], 1, 0, "%ls", SKULL_2);
		mvwprintw(v->win_champions[i], 2, 0, "%ls", SKULL_3);
		mvwprintw(v->win_champions[i], 3, 0, "%ls", SKULL_4);
		mvwprintw(v->win_champions[i], 4, 0, "%ls", SKULL_5);
		mvwprintw(v->win_champions[i], 5, 0, "%ls", SKULL_6);
		v->anim_flags[i] &= ~FLAG_ANIM_0;
	}
	wrefresh(v->win_champions[i]);
}

void	heal_life(t_viewer *v, int i)
{
	char step;

	step = 8;
	while (step--)
	{
		werase(v->win_champions[i]);
		if (step % 2)
			wattron(v->win_champions[i], A_BOLD);
		mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_1_100);
		mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_2_100);
		mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_3_100);
		mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_4_100);
		mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_5_100);
		mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_6_100);
		if (step % 2)
			wattroff(v->win_champions[i], A_BOLD);
		wrefresh(v->win_champions[i]);
		usleep(70000);
	}
	v->anim_flags[i] &= ~FLAG_ANIM_HEAL;
}

void	*th_anim_routine(void *p_data)
{
	t_anim		*a;

	a = (t_anim *)p_data;
	pthread_mutex_lock(&a->v->mutex);
	while (1)
	{
		if (a->v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&a->v->mutex);
			pthread_exit(0);
		}
		if (!(a->v->anim_flags[a->i] & FLAG_ANIM_0))
			draw_life(a->v, a->i, 0);
		else if (!(a->v->anim_flags[a->i] & FLAG_ANIM_25))
			draw_life(a->v, a->i, 25);
		else if (!(a->v->anim_flags[a->i] & FLAG_ANIM_50))
			draw_life(a->v, a->i, 50);
		else if (!(a->v->anim_flags[a->i] & FLAG_ANIM_75))
			draw_life(a->v, a->i, 75);
		else if (!(a->v->anim_flags[a->i] & FLAG_ANIM_100))
			draw_life(a->v, a->i, 100);
		else if (!(a->v->anim_flags[a->i] & FLAG_ANIM_HEAL))
			heal_life(a->v, a->i);
		else
			pthread_cond_wait(&a->v->cond, &a->v->mutex);
	}
	pthread_mutex_unlock(&a->v->mutex);
	pthread_exit(0);
}
