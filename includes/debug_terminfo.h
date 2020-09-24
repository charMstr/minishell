/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_terminfo.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 09:43:54 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:43:55 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_TERMINFO_H
# define DEBUG_TERMINFO_H

void	debug_start(void);
void	debug_end(void);
void	debug_escape_sequence(char *str);
void	debug_term_size(t_term *term);
void	debug_value_char(char c);
void	debug_cursor(t_int_pair *cursor);
void	debug_term_struct(t_term *term);
void	debug_clipboard_struct(t_clipboard clip);

#endif
