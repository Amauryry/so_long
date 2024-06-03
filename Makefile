# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberion <aberion@student.42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 00:00:00 by aberion           #+#    #+#              #
#    Updated: 2024/05/09 00:00:00 by aberion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = so_long

# Compilateur
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MINILIBX_LIB = minilibx-linux/libmlx.a
LIBFT_LIB = libft/libft.a
FT_PRINTF_LIB = ft_printf/libftprintf

# Include directories
INCLUDES = -I ./libft -I ./ft_printf -I ./minilibx-linux -I ./get_next_line

# Library paths
LFLAGS = -L ./libft -lft -L ./ft_printf -lftprintf -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lz

SRC_DIR = src/
OBJ_DIR = obj/

# Source files and object files
SRC = so_long.c check_map.c init_utils.c check_map_utils_2.c check_map_utils.c init.c free_and_co.c so_long_utils.c
OBJ = $(SRC:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(FT_PRINTF_LIB) $(MINILIBX_LIB) $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C ./libft

$(FT_PRINTF_LIB):
	$(MAKE) -C ./ft_printf

$(MINILIBX_LIB):
	$(MAKE) -C ./minilibx-linux

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./ft_printf clean
	$(MAKE) -C ./minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./ft_printf fclean
	$(MAKE) -C ./minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re libft ft_printf minilibx
