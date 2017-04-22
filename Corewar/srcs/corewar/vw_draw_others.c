/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_draw_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 10:09:07 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 11:02:53 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	heal(t_viewer *v, int i)
{
	t_anim *a;

	if (!(a = (t_anim *)ft_memalloc(sizeof(t_anim))))
		return ;
	a->v = v;
	a->i = i;
	v->anim_flags |= 1 << i;
	if (pthread_create(&v->th_anim[i], NULL, &th_anim_routine, a) < 0) {
		fprintf(stderr, "pthread_create error for th_anim[%d]\n", i);
		// BROADCAST QUIT
		exit(1);
	}
}

void 	draw_logo(t_viewer *v)
{
	mvwprintw(v->win_title, 0, 0, "%ls", LOGO_1);
	mvwprintw(v->win_title, 1, 0, "%ls", LOGO_2);
	mvwprintw(v->win_title, 2, 0, "%ls", LOGO_3);
	mvwprintw(v->win_title, 3, 0, "%ls", LOGO_4);
	mvwprintw(v->win_title, 4, 0, "%ls", LOGO_5);
	mvwprintw(v->win_title, 5, 0, "%ls", LOGO_6);
	mvwprintw(v->win_title, 6, 0, "%ls", LOGO_7);
	mvwprintw(v->win_title, 7, 0, "%ls", LOGO_8);
	mvwprintw(v->win_title, 8, 0, "%ls", LOGO_9);
	mvwprintw(v->win_title, 9, 0, "%ls", LOGO_10);
}
