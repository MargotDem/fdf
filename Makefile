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

SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) -c $(SRCS)
	gcc $(FLAGS) -o $(NAME) $(OBJS)

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# -lmlx -lXext -lX11