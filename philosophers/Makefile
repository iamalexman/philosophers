HEAD		= 	philo.h

HEAD2		=	bonus_philo.h

SRC			=	routine.c \
				philo_utils.c \
				main.c \
				init.c \

SRC2		=	bonus_routine.c \
				bonus_init.c \
				bonus_utils.c \
				bonus_main.c \

NAME		=	philo

NAME2		=	philo_bonus

OBJS		=	$(SRC:.c=.o)
OBJS2		=	$(SRC2:.c=.o)

CC			=	gcc

RM			= 	rm -rf

CFLAGS		= 	-Wall -Wextra -Werror

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS)		:	$(HEAD)

bonus		:	$(OBJS2)
				$(CC) $(CFLAGS) $(OBJS2) -o $(NAME2)

$(OBJS2)	:	$(HEAD2)

all			:	$(NAME) &(NAME2)

clean		:
				$(RM) $(OBJS) $(OBJS2)

fclean		:	clean
				$(RM) $(NAME) $(NAME2)

re			:	fclean	all

.PHONY		:	all clean fclean re bonus
