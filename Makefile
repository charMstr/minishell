# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 17:46:05 by charmstr          #+#    #+#              #
#    Updated: 2020/05/24 18:54:07 by mli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################ INCLUDE OTHER MAKEFILE ###########################
###############################################################################
#-include <file_name>.mk
# '-' so if the file does not exist --> silent
###############################################################################
###############################################################################


############################ SETTINGS #########################################
###############################################################################
CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = minishell
IFLAGS = -I $(INCLUDE_PATH_PROJECT)
LDFLAGS = -lft -lncurses

LIBFT = libft/libft.a 
DEPS = $(INCLUDES)
#DEPS_BONUS = $(INCLUDES_BONUS)
###############################################################################
###############################################################################

################## FOR COMPILATION WITH DEBUG #################################
###############################################################################
ifeq ($(f), n)
CFLAGS 		=
VALGRIND 	=
else ifeq ($(f), f)
CFLAGS 		+=  -fsanitize=address,undefined -g3
VALGRIND 	=
else ifeq ($(f), v)
CFLAGS 		+= -g3
SHOW_LEAK 	= --show-leak-kinds=definite
VALGRIND 	= valgrind --track-origins=yes --leak-check=full $(SHOW_LEAK)
endif
###############################################################################
###############################################################################


############################ PATHS ############################################
###############################################################################
OBJ_PATH = ./objects/
SRC_PATH = ./sources/
INCLUDE_PATH_PROJECT = ./includes/
LIB_PATH = -L ./libft/ 
###############################################################################
###############################################################################


########################### HEADER FILES ######################################
###############################################################################
H_FILES =	minishell\
			terminfo\
			lexing\
			builtin\
			parser\
			structures\
			historic\
			exe\
			debug_terminfo\
			debug_minishell\

#H_FILES_BONUS = #somefile\
				#someotherFile\

INCLUDES := $(patsubst %, $(INCLUDE_PATH_PROJECT)%.h, $(H_FILES))

# ADD EXTRANEOUS LIBRARY INCLUDES HERE
INCLUDES := $(INCLUDES) ./libft/libft.h

#INCLUDES_BONUS := $(patsubst %, $(INCLUDE_PATH_PROJECT)%.h, $(H_FILES_BONUS))
#INCLUDES_BONUS := $(INCLUDES_BONUS) ./libft/libft.h
###############################################################################
###############################################################################


########################### SRC/OBJ & BONUS FILES #############################
###############################################################################
SRC_FILES =	main\
			minishell_utils\
			lexer_root\
			lexer_find_token\
			lexer_quoted\
			lexer_operator\
			lexer_just_token\
			lexer_end\
			lexer_end2\
			builtin_env\
			builtin_unset\
			builtin_echo\
			builtin_export\
			input_root\
			termios_utils\
			terminfo_utils\
			terminfo_utils2\
			terminfo_cursor_position\
			terminfo_cursor_move\
			terminfo_cursor_move2\
			terminfo_cursor_move3\
			terminfo_del_character\
			terminfo_insert_character\
			terminfo_predict_size\
			terminfo_clipboard_root\
			terminfo_clipboard_action\
			read_root\
			read_process_char\
			historic_root\
			historic_update\
			historic_search\
			control_structure\
			parser_root\
			parser_cmd\
			parser_utils\
			parser_LIST_to_CMD_root\
			parser_LIST_to_CMD_assist\
			exe_root\
			cmd_expand_root\
			parameter_expansion\
			parameter_expansion2\
			quote_removal\
			field_splitting\
			debug_functions\
			debug_terminfo\
			btree_debug\
			debug_exe\

			#ft_printf\
			
#BONUS_FILES = 

SRC = $(patsubst %, $(SRC_PATH)%.c, $(SRC_FILES))
OBJ = $(patsubst %, $(OBJ_PATH)%.o, $(basename $(notdir $(SRC))))

#SRC_BONUS = $(patsubst %, $(SRC_PATH)%.c, $(BONUS_FILES))
#OBJ_BONUS = $(patsubst %, $(OBJ_PATH)%.o, $(basename $(notdir $(SRC_BONUS))))
###############################################################################
###############################################################################

###############################################################################
############################### COLOR CODE ####################################
REMOVE_FG = \033[38;5;196m 
CREAT_FG = \033[38;5;46m
BLACK_FG = \033[38;5;0m
BLACK_BG = \033[48;5;0m
CLEAR_COLOR = \033[m
NAME_BG = \033[48;5;39m 
OBJECTS_BG = \033[48;5;11m
###############################################################################
###############################################################################

all: $(NAME)

#| silent

silent:
	@:

.PHONY: all clean fclean re break_implicit_r

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@echo "\t\t$(CREAT_FG)created the $(OBJECTS_BG)$(BLACK_FG)$@ $(BLACK_BG)$(CREAT_FG) repository for $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG) $(CLEAR_COLOR)"

$(NAME): $(INCLUDES) $(LIBFT) $(OBJ) 
	@$(CC) $(CFLAGS) $(LIB_PATH) $(OBJ) -o $@ $(LDFLAGS)
	@echo "\t\t$(CREAT_FG)Binary $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(CREAT_FG) has been created$(CLEAR_COLOR)"
	@echo "\t\t$(CREAT_FG)We used the flags: $(CFLAGS)$(CLEAR_COLOR)\n"

$(OBJ): $(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPS) | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

bonus:

$(LIBFT): break_implicit_r
	@make -C ./libft

break_implicit_r: 

clean:
	@echo "\t\t$(REMOVE_FG)deleting $(OBJECTS_BG)$(BLACK_FG)$(OBJ_PATH) $(BLACK_BG)$(REMOVE_FG) containing all the .o files for $(NAME_BG)$(BLACK_FG)$(NAME) $(CLEAR_COLOR)"
	@rm -rf $(OBJ_PATH)
	@make fclean -C ./libft

fclean: clean
	@echo "\t\t$(REMOVE_FG)deleting $(NAME_BG)$(BLACK_FG)$(NAME) $(BLACK_BG)$(REMOVE_FG)...$(CLEAR_COLOR)" 
	@rm -rf $(NAME)

re: fclean all
