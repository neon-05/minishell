CC = cc

DEBUG = -fsanitize=address

CFLAGS = -Wall -Wextra -Werror -I$(LDIR) -I/usr/include
LFLAGS = -lreadline -L$(LDIR)

RM = rm -f

NAME = minishell
LIB = libft/libft.a

TESTEXE = helloworld
TESTSRC = helloworld.c

SRCS = \
	builtins/builtins.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_export.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c \
	exec.c \
	exec_utils.c \
	minishell.c \
	vars.c \

OBJS = $(SRCS:.c=.o)
LDIR = $(dir $(LIB))

all: $(NAME) $(TESTEXE)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIB) $(LFLAGS) -o $(NAME)

debug: $(OBJS) $(LIB)
	$(CC) $(DEBUG) $(OBJS) $(LIB) $(LFLAGS) -o $(NAME)

$(TESTEXE): $(TESTSRC)
	$(CC) $(TESTSRC) -o $@

%.a:
	$(MAKE) -C $(dir $@)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(MAKE) clean -C $(LDIR)
	$(RM) $(OBJS)

fclean:
	$(MAKE) fclean -C $(LDIR)
	$(RM) $(OBJS) $(NAME) $(TESTEXE)

re: fclean all

.PHONY: all clean fclean re
