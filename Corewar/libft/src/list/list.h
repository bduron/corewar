
#ifndef LIST_H
# define LIST_H
# include "libft.h"

typedef struct	s_lstelem
{
	void				*data;
	struct s_lstelem	*next;

}				t_lstelem;

typedef struct	s_lst
{
	t_lstelem	*head;
	t_lstelem	*tail;
	int			size;
	void		(*destroy)(void *data);
	void		(*match)(const void *key1, const void *key2);

}				t_lst;

void	lst_init(t_lst *list, (*destroy)(void *data));
void	lst_destroy(t_lst *list);
int		lst_ins_next(t_lst *list, t_lstelem *elem, const void *data);
int		lst_rem_next(t_lst *list, t_lstelem *elem, void **data);
#define lst_size(list) ((list)->size)
#define lst_head(list) ((list)->head)
#define lst_tail(list) ((list)->tail)
#define lst_is_head(list, elem) ((elem) == (list)->head ? 1 : 0)
#define lst_is_tail(elem) ((elem)->next == NULL ? 1 : 0)
#define lst_data(elem) ((elem)->data)
#define lst_next(elem) ((elem)->next)

#endif
