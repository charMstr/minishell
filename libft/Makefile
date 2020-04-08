# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charmstr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 21:40:12 by charmstr          #+#    #+#              #
#    Updated: 2020/01/30 16:04:00 by charmstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = libft.a
.PHONY = clean fclean re all bonus announcement
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
	strchr\
	strdup\
	strjoin\
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

SRC = $(patsubst %, $(OBJ_PATH)ft_%.c, $(FILES))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@echo "\t\t$(CREAT_FG)created the $(OBJECTS_BG)$(BLACK_FG)$@ $(BLACK_BG)$(CREAT_FG) repository for $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG) $(CLEAR_COLOR)"

$(NAME): announcement $(OBJ) $(FT_H)
	@ar -src $@ $(OBJ)

$(OBJ): $(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

announcement:
	@echo "\t\t$(CREAT_FG)building Library $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG)...$(CLEAR_COLOR)"

clean:
	@echo "\t\t$(REMOVE_FG)deleting $(OBJECTS_BG)$(BLACK_FG)$(OBJ_PATH) $(BLACK_BG)$(REMOVE_FG) containing all the .o files for $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG) $(CLEAR_COLOR)"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "\t\t$(REMOVE_FG)deleting $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(REMOVE_FG)...$(CLEAR_COLOR)" 
	@rm -rf $(NAME)

re: fclean all
