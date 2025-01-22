CC = cc

DEBUG = -fsanitize=address

CFLAGS = -Wall -Wextra -Werror -I$(LIB) -I/usr/include
LFLAGS = -lreadline -L$(LIB)

RM = rm -f

NAME = minishell
LIB = libft

SRCS = \
	main.c \
	envp.c \
	prompt.c \
	parsing/parser.c \
	parsing/parser_utils.c \
	parsing/tokenizer.c \
	parsing/tokenizer_utils.c \
	minishell_clean.c \
	debug.c \

DSRC = \
	vars.c \
	minishell_utils.c \

OBJS = $(SRCS:.c=.o)
DOBJ = $(DSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB)/libft.a $(LFLAGS) -o $(NAME)
	@echo $(NAME)" compiled!"

debug: $(OBJS) $(LIB)
	$(CC) $(DEBUG) $(OBJS) $(LIB)/libft.a $(LFLAGS) -o $(NAME)
	@echo $(NAME)" compiled with address sanitizer!"

vars: $(OBJS) $(DOBJ) $(LIB)
	$(CC) $(DOBJ) $(LIB)/libft.a $(LFLAGS) -o vars

$(LIB):
	$(MAKE) -C $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(MAKE) clean -C $(LIB)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIB)

