#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/22 19:38:08 by kstorozh          #+#    #+#              #
#    Updated: 2017/05/22 20:36:49 by kstorozh         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

HEADER = fractol.h

SRC =	main.c colour.c julia.c maldebrot.c pyfagor.c additional.c print.c image.c key_funk.c button_funk.c string_funk.c add_params.c pyfagor_time.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADER)
	gcc  $(CFLAGS) -c -o $@ $< 

$(NAME): $(OBJ)
	@make -C libft/	
	gcc -o $@ $(OBJ) -L libft -lft libft/libft.a -lmlx -framework OpenGL -framework AppKit

clean:
	@make clean -C libft/ 
	rm -f $(OBJ)

fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

re: fclean all
