NAME		= cub3D.a

NAME_BONUS	= cub3D_bonus.a

EXEC		= cub3D

EXEC_BONUS	= cub3D_bonus

SRCS		=	

SRCS_BONUS	=	

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

.c.o:
	$(CC) $(CFLAGS) -Imlx -c -I./ $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
	ar -rc $(NAME) $(OBJS)
	$(CC) -lmlx -framework OpenGL -framework AppKit $(NAME) -o $(EXEC) -lm

$(NAME_BONUS):	$(OBJS_BONUS)
	ar -rc $(NAME_BONUS) $(OBJS_BONUS)
	$(CC) -lmlx -framework OpenGL -framework AppKit $(NAME_BONUS) -o $(EXEC_BONUS) -lm -O2 -O3 -Os

all:	$(NAME)

bonus:	$(NAME_BONUS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean:	clean
	$(RM) $(NAME) $(EXEC)
	$(RM) $(NAME_BONUS) $(EXEC_BONUS)

re:	fclean all


.PHONY:	all clean fclean re