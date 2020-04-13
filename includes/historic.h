#ifndef HISTORIC_H
# define HISTORIC_H


t_dlist		*ft_dlstnew(void *content);
void		ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void		ft_dlstadd_front(t_dlist **alst, t_dlist *new);
t_dlist		*ft_dlstlast(t_dlist *lst);
t_dlist		*ft_dlstfirst(t_dlist *lst);
void		ft_dlstclear(t_dlist **lst, void (*del)(void *));
void		ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void		ft_dlstpop_front(t_dlist **head, void (*del)(void*));
void		ft_dlstpop_back(t_dlist **head, void (*del)(void*));

t_history	*history_init_struct(void);
void		history_del_content(void *content);
int			history_add_new_link(t_control *control);
int			history_append_line(t_control *control, t_history *history);
int			history_decide_discard_new_link(t_control *control);

void		history_search(t_control *control, int direction);
int			history_swap_line_in_term_struct(t_control *control, int up);
int			history_terminfo_reset_cursor(t_control *control, t_int_pair \
			*cursor_end);

#endif
