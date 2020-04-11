#ifndef TERMINFO_H
# define TERMINFO_H

# define KEY_ESC_ "\033"
# define KEY_ESC_ID 0x00
# define KEY_UP_ "\033[A"
# define KEY_UP_ID 0x01
# define KEY_RIGHT_ "\033[C"
# define KEY_RIGHT_ID 0x02
# define KEY_LEFT_ "\033[D"
# define KEY_LEFT_ID 0x03
# define KEY_DOWN_ "\033[B"
# define KEY_DOWN_ID 0x04
# define KEY_HOME_ "\033[H"
# define KEY_HOME_ID 0x05
# define KEY_DELETE_ "\033[3~"
# define KEY_DELETE_ID 0x06
# define KEY_END_ "\033[F"
# define KEY_END_ID 0x07
# define KEY_PAGE_UP_ "\033[5~"
# define KEY_PAGE_UP_ID 0x08
# define KEY_PAGE_DOWN_ "\033[6~"
# define KEY_PAGE_DOWN_ID 0x09
# define KEY_UP_CTRL_ "\033[1;5A"
# define KEY_UP_CTRL_ID 0x0A
# define KEY_DOWN_CTRL_ "\033[1;5B"
# define KEY_DOWN_CTRL_ID 0x0B
# define NUMBER_SPECIAL_KEYS 12

# define CTRL_A_COMBO 0x01
# define CTRL_E_COMBO 0x05


//# include "structures.h"
# include "../libft/libft.h"

int			master_loop(t_control *control);

void		control_init_struct(t_control *control);
void		control_free_struct(t_control *control);

t_list		*input_root(t_control *control);
t_list		*input_root_assist_and_prompt(t_control *control);
int			input_reset_term_struct(t_control *control);
t_list		*input_reading_and_lexing(t_control *control);
int			input_check_for_stop_condition(t_control *control);

int			termios_enable_raw_mode(struct termios *old);
void		termios_reset_cooked_mode(struct termios *saved_copy);

t_term		*terminfo_init_database(void);
t_term		*terminfo_init_struct(void);
void		*terminfo_free_struct(t_term *term);
int			terminfo_load_win_size(t_term *term);
void		terminfo_reset_terminal(void);

int			terminfo_load_array_esc_seq(t_term *term);
char		*terminfo_get_caps(char *caps_id, t_control *control);
char		*terminfo_edit_caps(t_control *control, char *caps_id, int param);

// need to complet this file
int			terminfo_del_char(t_control *control);

int			terminfo_insert_char(t_control *control, char c);
int			terminfo_insert_in_place(t_control *control, char c);
int			terminfo_insert_char_cascade(t_control *control);

int			terminfo_cursor_get_pos(t_control *control, t_int_pair *curs);
void		terminfo_cursor_get_pos_assist(char *caps, t_int_pair *cursor);
int			terminfo_get_prompt_len(t_control *control);
int			terminfo_cursor_save_reset(t_control *control, int save);

void		terminfo_cursor_move_right(t_control *control);
void		terminfo_cursor_move_left(t_control *control);
int			terminfo_cursor_move(t_control *control, int x, int y);
int			terminfo_cursor_move_diagonally(t_control *control, int diag);
int			terminfo_cursor_move_endl(t_control *control, int start);

void		terminfo_cursor_move_up(t_control *control);
void		terminfo_cursor_move_down(t_control *control);

int			input_read_line(t_term *term);

void		read_root(t_control *control, int read_res, char c);
int			read_get_esc_seq_id(t_term *term, char c);
int			read_need_to_stop(t_control *control, char c, int res);
void		read_dispatch_for_processing(t_control *control, char c);
void		read_process_special_key(t_control *control, char c);

void		read_process_del_char(t_control *control);
void		read_process_add_char(t_control *control, char c);
int			ft_strinject(char **str, char c, int index);

void		read_process_control_combo(t_control *control, char c);

#endif
