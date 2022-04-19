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

SRCS = fdf.c handle_error.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I/usr/local/include

LIBS = -L /usr/local/lib -lmlx

FRAMEWORKS = -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME):
	make -C ./libft
	cp ./libft/libft.a ./libft.a
	gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -L./ -lft $(LIBS) $(FRAMEWORKS)

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# gcc -Wall -Werror -Wextra fdf.c handle_error.c -L./ -lft
# -lmlx -lXext -lX11
