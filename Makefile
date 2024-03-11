NAME = pipex
CC = cc
CCFLAGS = -Wextra -Wall -Werror
RM = rm -f
DEBUG = -g

HEADDIR = .
HEADERS = pipex.h

SRCS =	main.c \
		params.c \

OBJSDIR = ./objs/
OBJSLIST = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJSDIR), $(OBJSLIST))

LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a

LIBS = -L${LIBFTDIR} -lft
INCS = -I${HEADDIR} -I${LIBFTDIR}

all: $(NAME)

$(NAME): $(LIBFT) $(OBJSDIR) $(OBJS)
	$(CC) $(FLAGS) $(DEBUG) $(OBJS) -o $@ $(LIBS) $(INCS)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(OBJSDIR)%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(DEBUG) $(INCS) -c $< -o $@

clean:
	$(RM) -r $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re

# test: re
# 	./$(NAME) test_maps/42.fdf
