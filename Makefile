# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 16:28:19 by vmondor           #+#    #+#              #
#    Updated: 2024/05/15 15:45:17 by vmondor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Werror -Wextra

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a

HEADERS			= $(SRC_PATH)minishell.h

SRC_PATH		= src/
OBJ_PATH		= src/obj/

SRC_FILES		=	main.c							\
					pipex/pipex.c					\
					pipex/parsing_pipex.c			\
					pipex/pipex_utils.c				\
					pipex/pipex_utils_next.c		\
					pipex/get_path.c				\
					pipex/init_values.c				\
					pipex/get_next_line_utils.c		\
					pipex/get_next_line.c			\
					pipex/process.c					\
					pipex/convert_var_to_cmd.c		\
					pipex/execute_command.c			\
					pipex/error.c					\
					pipex/here_doc.c				\
					pipex/here_doc_utils.c			\
					pipex/set_token.c				\
					pipex/set_input.c				\
					pipex/set_output.c				\
					pipex/utils_for_all.c			\
					parsing.c						\
					split_args.c					\
					split_args_utils.c				\
					check_quotes.c					\
					t_cmd_utils.c					\
					utils.c							\
					builtins.c						\
					echo.c							\
					echo_utils.c					\
					echo_split.c					\
					echo_split_utils.c				\
					cd.c							\
					env.c							\
					pwd.c							\
					exit.c							\
					export.c						\
					unset.c							\
					signaux.c						\
					signaux_utils.c					\
					minishell.c						\

OBJ_FILES		= $(SRC_FILES:.c=.o)
OBJS			= $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: $(OBJ_PATH) $(OBJ_PATH)pipex/ ${NAME}

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)pipex/:
	mkdir -p $(OBJ_PATH)pipex/

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
