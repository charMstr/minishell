#ifndef LEXING_H
# define LEXING_H

typedef struct	s_token
{
	char		*str;
	int			id;
	unsigned int open_quote:1;
	unsigned int esc_next:1;
}				t_token;

# define TOKEN 0
# define SEMI 1
# define PIPE 2
# define OR_IF 3
# define AND 4
# define AND_IF 5
# define LBRACE 6
# define RBRACE 7
# define S_QUOTE 8
# define D_QUOTE 9
# define LESS 10
# define DLESS 11
# define GREAT 12
# define DGREAT 13

t_list	*lexer_root(char *input);
t_token	*lexer_build_next_token(const char *input, int *j);
t_token	*lexer_init_token(void);
void	del_token(void *token);

int		lexer_find_token(const char *input, int *j, t_token *token);
int		ft_append_char(char **str, char c);
int		lexer_jump_esc(int *j, t_token *token);

int		lexer_operator(const char *input, int *j, t_token *token);
int		lexer_operator2(const char *input, int *j, t_token *token);
void	lexer_set_operator_id(t_token *token, char c);

int		lexer_quoted(const char *input, int *j, t_token *token);
int		lexer_quoted_single(const char *input, char c, int *j, t_token *token);
int		lexer_quoted_double(const char *input, char c, int *j, t_token *token);

int		lexer_just_token(const char *input, int *j, t_token *token);
int		lexer_token_or_indirection(const char *input, int *j, t_token *token);
int		lexer_indirection(const char *input, int *j, t_token *token);

#endif
