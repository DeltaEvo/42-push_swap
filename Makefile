# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:01:17 by dde-jesu          #+#    #+#              #
#    Updated: 2019/02/22 15:00:25 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Wextra -Werror -Iinclude -Ilibft/include
CC=gcc

include src.mk

OBJS=$(filter-out src/checker.o src/push_swap.o, $(SRCS:.c=.o))

all: checker push_swap

$(OBJS): Makefile src.mk

libft/libft.a:
	$(MAKE) -C libft libft.a

checker: $(OBJS) src/checker.o libft/libft.a
	$(CC) -o $@ $^

push_swap: $(OBJS) src/push_swap.o libft/libft.a
	$(CC) -o $@ $^
	
clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) src/checker.o src/push_swap.o

fclean: clean
	$(MAKE) -C libft fclean
	rm -rf checker push_swap

re: fclean all

.PHONY: clean fclean re all
