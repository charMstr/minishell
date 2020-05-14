#ifndef HISTORIC_H
# define HISTORIC_H

int			history_root(t_control *control, t_history *history);
t_history	*history_init_struct(void);
void		history_del_content(void *content);
int			history_add_new_link(t_control *control);

void		history_search(t_control *control, int direction);
int			history_swap_line_in_term_struct(t_control *control, int up);

int			history_update_line_insert_sep(t_control *control, \
		t_history *history);
int			history_update_line(t_control *control, t_history *history);
int			history_decide_discard_new_link(t_control *control);

#endif
