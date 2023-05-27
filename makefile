SRCS	= src/main.c src/hooks.c src/points.c src/utils.c src/struct.c gnl/get_next_line.c gnl/get_next_line_utils.c 

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

LIB		= -Ignl -lm -lmlx -framework OpenGL -framework Appkit -L inc/minilibx_macos

RM		= rm -rf

NAME	= fdf

all:	$(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(NAME)
clean:
		$(RM) $(OBJS)
fclean: clean
		$(MAKE) clean 
		$(RM) $(NAME)
re:     fclean
		$(NAME)
.PHONY: all clean fclean re
