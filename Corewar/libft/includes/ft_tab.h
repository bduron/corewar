/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:16:37 by kcosta            #+#    #+#             */
/*   Updated: 2017/02/18 15:20:28 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAB_H
# define FT_TAB_H

# include "stdlib.h"
# include "string.h"

void		ft_tabdel(char ***tab);
size_t		ft_tablen(char **tab);
char		**ft_tabstr(char **tab, char *entry);

#endif
