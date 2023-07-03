# ============================================================================= #
#                                 █████      ████████  ██████████  				#
#                                ░░███      ███░░░░███░░███░░░░███ 				#
#              ██████  █████ ████ ░███████ ░░░    ░███ ░███   ░░███				#
#             ███░░███░░███ ░███  ░███░░███   ██████░  ░███    ░███				#
#            ░███ ░░░  ░███ ░███  ░███ ░███  ░░░░░░███ ░███    ░███				#
#            ░███  ███ ░███ ░███  ░███ ░███ ███   ░███ ░███    ███ 				#
#            ░░██████  ░░████████ ████████ ░░████████  ██████████  				#
#             ░░░░░░    ░░░░░░░░ ░░░░░░░░   ░░░░░░░░  ░░░░░░░░░░   				#
# ============================================================================= #
                                                      
NAME		= cub3D

# ============================================================================= #

SRC			= cub.c mlx_handler.c \

# ============================================================================= #

SRCS		= $(addprefix srcs/, $(SRC))

OBJS		= $(SRCS:.c=.o)

# ============================================================================= #

LDFLAGS		= -lmlx -framework OpenGL -framework AppKit

# ============================================================================= #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -I./includes/ -Imlx 

RM			= rm -f

.c.o:
	$(CC) $(CFLAGS) -Imlx -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# ============================================================================= #

all:	$(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean:	clean
	$(RM) $(NAME) $(EXEC)
	$(RM) $(NAME_BONUS) $(EXEC_BONUS)

re:	fclean all

.PHONY:	all clean fclean re

# ============================================================================= #
