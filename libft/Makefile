# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charmstr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 21:40:12 by charmstr          #+#    #+#              #
#    Updated: 2020/06/20 22:07:34 by mli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = libft.a
.PHONY = clean fclean re all bonus
FT_H = ./libft.h
OBJ_PATH = ./objects/
INCLUDE_PATH = ./
I_FLAGS = -I $(INC_PATH)

REMOVE_FG = \033[38;5;196m 
CREAT_FG = \033[38;5;46m
BLACK_FG = \033[38;5;0m
BLACK_BG = \033[48;5;0m
CLEAR_COLOR = \033[m

NAME_BG = \033[48;5;39m 
OBJECTS_BG = \033[48;5;11m
RANLIB_BG = \033[48;5;172m

FILES = atoi\
	bzero\
	calloc\
	isalnum\
	isalpha\
	isascii\
	isdigit\
	isprint\
	isonly\
	isonly_ft\
	itoa\
	memccpy\
	memchr\
	memcmp\
	memcpy\
	memmove\
	memset\
	stringify\
	putchar_fd\
	putendl_fd\
	putnbr_fd\
	putstr_fd\
	split\
	split_whitespaces\
	strchr\
	strdup\
	strjoin\
	strjoin_free\
	strlcat\
	strlcpy\
	strlen\
	strmapi\
	strncmp\
	strnstr\
	strrchr\
	strtrim\
	substr\
	tolower\
	toupper\
	lstadd_back\
	lstadd_front\
	lstclear\
	lstdelone\
	lstiter\
	lstlast\
	lstmap\
	lstnew\
	lstsize\
	lstrev\
	lstfind\
	itoa_base\
	size_num_base_signed\
	strrev\
	strichr\
	putbits_fd\
	putbytes_fd\
	array_dup\
	array_free\
	stristr\
	array_len\
	strappend\
	abs\
	atoi_ptr\
	itoa_lbase\
	memalloc\
	nbrlen\
	putchar\
	putnbr\
	putstr\
	strcmp\
	free\
	strcadd\
	strcdel\
	strstradd\
	dlstnew\
	dlstadd_back\
	dlstadd_front\
	dlstlast\
	dlstfirst\
	dlstclear\
	dlstdelone\
	dlstpop_front\
	dlstpop_back\
	dlstclearback_addr\
	lstremove_if\
	ptrswap\

NO_FT_FILES = btree_add\
			  btree_apply_bfs\
			  btree_apply_infix\
			  btree_apply_prefix\
			  btree_apply_suffix\
			  btree_depth\
			  btree_find\
			  btree_new\
			  btree_clear\
			  btree_delone\

SRC = $(patsubst %, $(OBJ_PATH)ft_%.c, $(FILES)) \
	  $(patsubst %, $(OBJ_PATH)%.c, $(NO_FT_FILES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@echo "\t\t$(CREAT_FG)created the $(OBJECTS_BG)$(BLACK_FG)$@ $(BLACK_BG)$(CREAT_FG) repository for $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CLEAR_COLOR)"

$(NAME): $(OBJ) $(FT_H)
	@ar -src $@ $(OBJ)
	@echo "\t\t$(CREAT_FG)Library $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG) has been created$(CLEAR_COLOR)"

$(OBJ): $(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@echo "\t\t$(REMOVE_FG)deleting $(OBJECTS_BG)$(BLACK_FG)$(OBJ_PATH) $(BLACK_BG)$(REMOVE_FG) containing all the .o files for $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CLEAR_COLOR)"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "\t\t$(REMOVE_FG)deleting $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(REMOVE_FG)...$(CLEAR_COLOR)" 
	@rm -rf $(NAME)

re: fclean all
