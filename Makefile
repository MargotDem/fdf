# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-maul <mde-maul@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 17:58:11 by mde-maul          #+#    #+#              #
#    Updated: 2022/04/10 17:58:14 by mde-maul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  fdf

SRCS = fdf.c handle_error.c parse_map.c create_mlx_win_struct.c open_mlx.c \
	handle_key_events.c draw_map.c draw_line.c helpers.c malloc_free_map.c \
	get_map_size.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I/usr/local/include

LIBS = -L /usr/local/lib -lmlx

FRAMEWORKS = -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -L ./libft -lft $(LIBS) \
		$(FRAMEWORKS)

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

dev:
	rm -f $(NAME)
	gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -L ./libft -lft $(LIBS) \
		$(FRAMEWORKS)
	make clean

