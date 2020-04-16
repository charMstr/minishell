#ifndef DEBUG_H
# define DEBUG_H

void	debug_start(void);
void	debug_end(void);
void	debug_escape_sequence(char *str);
void	debug_term_size(void);
void	debug_value_char(char c);
void	debug_cursor(t_int_pair *cursor);
void	debug_term_struct(t_term *term);
void	debug_clipboard_struct(t_clipboard clip);

#endif
