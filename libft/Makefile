# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                              ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 21:10:40 by smamalig          #+#    #+#              #
#    Updated: 2025/06/12 15:16:20 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    #
#                                                                              #
# **************************************************************************** #

NAME        = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -MMD -MP -O0
SRC_DIR     = src
OBJ_DIR     = obj
PRINTF_SRCS = conversion.c dprintf.c format.c handlers.c parse_format.c \
	parser.c print_hex.c print_signed.c print_str.c print_unsigned.c printf.c \
	save_pos.c snprintf.c sprintf.c strerror.c util.c util2.c vdprintf.c \
	vprintf.c vsnprintf.c vsprintf.c
SRC_FILES   = calloc.c malloc.c memcpy.c mempcpy.c memset.c split.c stpcpy.c \
	strcpy.c strdup.c strlen.c strncmp.c strcmp.c memchr.c realloc.c \
	get_next_line.c $(addprefix printf/, $(PRINTF_SRCS))
SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(patsubst $(SRC_DIR)/%.c, ${OBJ_DIR}/%.o, $(SRCS))
DEPS        = $(patsubst $(SRC_DIR)/%.c, ${OBJ_DIR}/%.d, $(SRCS))
INCLUDES    = -Iinclude

# Colors
RED         = \e[31m
GREEN       = \e[32m
YELLOW      = \e[33m
BLUE        = \e[34m
MAGENTA     = \e[35m
CYAN        = \e[36m
RESET       = \e[m

ifeq ($(DEBUG), 1)
	CFLAGS += -Wpedantic -g3
else
	CFLAGS += -Werror
endif

ifeq ($(USE_ERRNO), 1)
	CFLAGS += -DUSE_ERRNO
endif

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(BLUE)%s$(RESET): $(YELLOW)Building$(RESET) $(NAME)\n" $(NAME)
	@ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)%s$(RESET): $(MAGENTA)Compiling$(RESET) $<\n" $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
	@-norminette | grep -v "OK"

clean:
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) object files\n" $(NAME)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) executables and libraries\n" $(NAME)
	@rm -f $(NAME)

re: fclean
	@make all --no-print-directory

-include $(DEPS)

.PHONY: all clean fclean re norm
