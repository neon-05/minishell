# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 00:28:46 by malapoug          #+#    #+#              #
#    Updated: 2025/04/17 15:39:57 by malapoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

DEBUG = -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

SRCS_PARSING = parser.c\
	parser_utils.c\
	tokenizer.c\
	tokenizer_utils.c\
	limiter.c\
	redirections.c\
	debug.c\
	clean.c\
	struct.c\
	in_and_out.c\

SRCS = main.c\
	envp.c\
	prompt/prompt.c\
	$(addprefix parsing/, $(SRCS_PARSING))\
	lib_utils/ft_split_let.c\
	lib_utils/ft_strjoin_f.c\
	lib_utils/ft_free_arr.c\

OBJS = $(SRCS:.c=.o)

RM = rm -f


all: $(NAME)

$(NAME): $(OBJS)
	@make -C 42_libft/
	@make -C lib_utils/libft/
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -lreadline -o $(NAME)
	@echo $(NAME)" compiled!\n"

debug: $(OBJS)
	@make -C 42_libft/
	@make -C lib_utils/libft/
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) libft/libft.a  -lreadline -o $(NAME)
	@echo $(NAME)" compiled with debug!\n"

%.o: %.c
	@$(CC) $(CFLAGS) -g -gdwarf-4 -I/usr/include -lreadline -c $< -o $@


clean:
	@make clean -C 42_libft/
	@make clean -C lib_utils/libft/
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C 42_libft/
	@make clean -C lib_utils/libft/
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

