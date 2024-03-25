NAME = pipex
CC = cc
CCFLAGS = -Wextra -Wall -Werror
RM = rm -f
DEBUG = -g

HEADDIR = .
HEADERS = pipex.h
HEADERS_BONUS = pipex_bonus.h

SRCS =			cmd.c \
				main.c \
				pipex.c \
				utils.c \

SRCS_BONUS =	cmd_bonus.c \
				main_bonus.c \
				param_bonus.c \
				pipex_bonus.c \
				utils_bonus.c \
				here_doc.c \

OBJSDIR = ./objs/
OBJSDIR_BONUS = ./objs_bonus/
OBJSLIST = $(SRCS:.c=.o)
OBJSLIST_BONUS = $(SRCS_BONUS:.c=.o)
OBJS = $(addprefix $(OBJSDIR), $(OBJSLIST))
OBJS_BONUS = $(addprefix $(OBJSDIR_BONUS), $(OBJSLIST_BONUS))

LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a

LIBS = -L${LIBFTDIR} -lft
INCS = -I${HEADDIR} -I${LIBFTDIR}

all: $(NAME)

bonus: $(LIBFT) $(OBJSDIR_BONUS) $(OBJS_BONUS)
	$(CC) $(FLAGS) $(DEBUG) $(OBJS_BONUS) -o $(NAME) $(LIBS) $(INCS)

$(NAME): $(LIBFT) $(OBJSDIR) $(OBJS)
	$(CC) $(FLAGS) $(DEBUG) $(OBJS) -o $@ $(LIBS) $(INCS)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(OBJSDIR_BONUS):
	mkdir -p $(OBJSDIR_BONUS)

$(OBJSDIR)%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(DEBUG) $(INCS) -c $< -o $@

$(OBJSDIR_BONUS)%.o: %.c $(HEADERS_BONUS)
	$(CC) $(FLAGS) $(DEBUG) $(INCS) -c $< -o $@

clean:
	$(RM) -r $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean bonus re

