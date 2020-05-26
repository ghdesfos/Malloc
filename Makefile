# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/10 21:51:54 by ghdesfos          #+#    #+#              #
#    Updated: 2019/05/21 15:57:11 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so
SRC = 	malloc.c\
		malloc_small.c\
		malloc_medium.c\
		malloc_large.c\
		get_right_space_in_mmap_area_small.c\
		get_right_space_in_mmap_area_medium.c\
		free.c\
		free_small.c\
		free_medium.c\
		free_large.c\
		realloc.c\
		realloc_small.c\
		realloc_medium.c\
		realloc_large.c\
		print_mmap_areas.c\
		print_mmap_areas_sub.c\
		show_alloc_mem.c
FILES = $(addprefix sources/, $(SRC))
OBJ = $(FILES:.c=.o)
INCLUDES = includes/
HEADERS = includes/header.h

FLAGS =-Wall -Wextra -Werror
B_PRINTF_FOLD = b_printf
B_PRINTF_NAME = ftprintf
EXEC = test

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(B_PRINTF_FOLD)
	gcc $(FLAGS) -shared -L$(B_PRINTF_FOLD) -l$(B_PRINTF_NAME) -o $@ $^
	ln -sf $(NAME) $(LINK)

%.o: %.c $(HEADERS)
	gcc $(FLAGS) -I $(B_PRINTF_FOLD) -I $(INCLUDES) -fpic -c -o $@ $<

exec: re
	gcc ./test_files/main.c -I. -I $(B_PRINTF_FOLD) -I $(INCLUDES) -L. -lft_malloc -o $(EXEC)
	./config.sh ./$(EXEC)

clean:
	make clean -C $(B_PRINTF_FOLD)
	/bin/rm -f $(OBJ)
	/bin/rm -f $(EXEC)
	/bin/rm -rf *.dSYM

fclean: clean
	make fclean -C $(B_PRINTF_FOLD)
	/bin/rm -f $(NAME)
	/bin/rm -f $(LINK)

re: fclean all

.PHONY: all exec clean fclean re
