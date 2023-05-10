# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gade-alm <gade-alm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 10:52:52 by gabriel           #+#    #+#              #
#    Updated: 2023/05/10 12:53:09 by gade-alm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(SRCS_DIR)/main.c \
			$(SRCS_DIR)/utils/utils.c	\
			$(SRCS_DIR)/parse/split.c \
			$(SRCS_DIR)/parse/utils_parse.c \
			$(SRCS_DIR)/parse/utils_parse_2.c \
			$(SRCS_DIR)/parse/handle_cmd.c \
			$(SRCS_DIR)/parse/parse_main.c \
			$(SRCS_DIR)/parse/parse_main_utils.c \
			$(SRCS_DIR)/exp/expander.c \
			$(SRCS_DIR)/exp/exp_utils.c \
			$(SRCS_DIR)/exp/remove_quotes.c \
			$(SRCS_DIR)/env/env.c \
			$(SRCS_DIR)/utils/allocation.c \
			$(SRCS_DIR)/utils/strings.c \
			$(SRCS_DIR)/utils/strings1.c \
			$(SRCS_DIR)/env/path.c \
			$(SRCS_DIR)/executor/executor.c \
			$(SRCS_DIR)/executor/heredocs.c \
			$(SRCS_DIR)/executor/exec_utils.c \
			$(SRCS_DIR)/executor/signals.c \
			$(SRCS_DIR)/utils/struct.c \
			$(SRCS_DIR)/builtins/builtins.c \
			$(SRCS_DIR)/builtins/builtins1.c \
			$(SRCS_DIR)/builtins/utils.c \
			$(SRCS_DIR)/lists/listutils_01.c \
			$(SRCS_DIR)/lists/listutils_02.c \

SRCS_DIR	= srcs

OBJS		= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

OBJS_DIR	= objs

NAME		= minishell

ifeq ($(shell uname -s), Linux)
	INC		= -I inc -I /usr/include/readline
	LIBS	= -lreadline
else
	INC		= -I inc -I /opt/homebrew/include/readline
	LIBS	= -L /opt/homebrew/lib -lreadline
endif

CC			= cc

CFLAGS 		= -Wall -Wextra -Werror $(INC) -g #-fsanitize=address

RM 			= rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
		@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -lreadline -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR) a.out
	
fclean: clean
	$(RM) $(NAME) $(OBJS)
valgrind:	re
	valgrind --suppressions=txt/.ignore_readline --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --log-file=valgrind-out.txt ./minishell

re: fclean all
