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

SRCS		= cub.c \

MLX			= mlx_handler.c xpm_texture.c \

GNL			= get_next_line.c get_next_line_utils.c \

LIBFT		= ft_memcpy.c ft_split.c ft_strcmp.c ft_strdup.c ft_strlen.c \
				ft_substr.c ft_strtrim.c ft_atoi.c ft_isdigit.c ft_tabdup.c \
				ft_lstadd_back.c ft_lstclear.c ft_lstnew.c ft_bzero.c \
				ft_strreverse.c \

MAP			= parsing.c check_parsing.c check_map.c map_to_data.c \

# ============================================================================= #

BASE_SRC	= $(addprefix srcs/, $(SRCS))
MLX_SRC		= $(addprefix srcs/mlx/, $(MLX))
GNL_SRC		= $(addprefix srcs/gnl/, $(GNL))
LIBFT_SRC	= $(addprefix srcs/libft/, $(LIBFT))
MAP_SRC		= $(addprefix srcs/map_parsing/, $(MAP))

# ============================================================================= #

BASE_OBJS	= $(BASE_SRC:.c=.o)
MLX_OBJS	= $(MLX_SRC:.c=.o)
GNL_OBJS	= $(GNL_SRC:.c=.o)
LIBFT_OBJS	= $(LIBFT_SRC:.c=.o)
MAP_OBJS	= $(MAP_SRC:.c=.o)

ALL_OBJS	= $(BASE_OBJS) $(MLX_OBJS) $(GNL_OBJS) $(LIBFT_OBJS) $(MAP_OBJS)

# ============================================================================= #

LDFLAGS		= -lmlx -framework OpenGL -framework AppKit

# ============================================================================= #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -I./includes/ -O3
#  -g3 -fsanitize=address
RM			= rm -f

.c.o:
	$(CC) $(CFLAGS) -Imlx -c $< -o ${<:.c=.o}

$(NAME):	$(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LDFLAGS) -o $(NAME)

# ============================================================================= #

all:	$(NAME)

clean:
	$(RM) $(ALL_OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

# ============================================================================= #
