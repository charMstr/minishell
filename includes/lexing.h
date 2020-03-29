#ifndef LEXING_H
# define LEXING_H

typedef struct	s_token
{
	char		*str;
	int			id;
	int			quoted;
}				t_token;

typedef struct	s_lexing
{
	unsigned int	operator:1;
	unsigned int	empty:1;
	unsigned int	s_quoted:1;
	unsigned int	d_quoted:1;
	unsigned int	esc_next:1;
	unsigned int	is_alpha:1;
	unsigned int	is_num:1;
}				t_lexing;

t_list	*lexer_root(char *input);
void	lexer_init_lexing_struct(t_lexing * lex);
t_token	*lexer_build_next_token(const char *input, int *j);
char	*lexer_find_token(const char *input, int *j, t_lexing lex);
char	*ft_stradd_char(char *str, char c);
t_token	*lexer_init_token(void);
void	lexer_update_lexing_struct(char c, t_lexing *lex);
char	*lexer_operator(const char *input, char *token_str, int *j, t_lexing *lex);

#endif
