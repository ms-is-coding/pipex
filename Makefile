# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 15:13:52 by smamalig          #+#    #+#              #
#    Updated: 2025/05/06 15:36:33 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = pipex
CC        = cc
CFLAGS    = -Wall -Wextra
SRC_FILES = main.c
SRC_DIR   = src
SRCS      = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR   = obj
OBJS      = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
LDFLAGS   = -Llibft -lft
INCLUDES  = -Iinclude -Ilibft/include

ifeq ($(DEBUG), 1)
	CFLAGS += -Wpedantic -O0 -g3
else
	CFLAGS += -Werror -O3
endif

RED    = \e[31m
GREEN  = \e[32m
YELLOW = \e[33m
BLUE   = \e[34m
PURPLE = \e[35m
CYAN   = \e[36m
RESET  = \e[m

all: $(NAME)

$(NAME): libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft:
	@make -C libft --no-print-directory

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re libft
