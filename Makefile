# **************************************************************************** #
#                                                                              #
#                                                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    #
#    Makefile                                              ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀    #
#                                                          ⠀⠀⢀⣴⣿⠟⠁⠀⠀⠀⠁⢀⣼⣿⠟⠀    #
#    By: smamalig <smamalig@student.42.fr>                 ⠀⣴⣿⣟⣁⣀⣀⣀⡀⠀⣴⣿⡟⠁⢀⠀    #
#                                                          ⠀⠿⠿⠿⠿⠿⣿⣿⡇⠀⣿⣿⣇⣴⣿⠀    #
#    Created: 2025/05/26 15:05:17 by smamalig              ⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀    #
#    Updated: 2025/06/13 08:17:16 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀    #
#                                                                              #
# **************************************************************************** #

NAME        = pipex
CC          = cc
CFLAGS      = -Wall -Wextra -MMD -MP
SRC_FILES   = main.c tokenize.c error.c argument.c exec.c
SRC_DIR     = src
OBJ_DIR     = obj
SRCS       := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS       := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS       := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))
INCLUDES    = -Iinclude -Ilibft/include

RED         = \e[31m
GREEN       = \e[32m
YELLOW      = \e[33m
BLUE        = \e[34m
MAGENTA     = \e[35m
CYAN        = \e[36m
RESET       = \e[m

LIBFT       = libft
LIBFT_FLAGS = -Llibft -lft
LIBFT_DIR   = ./libft

LDFLAGS = $(LIBFT_FLAGS)

ifeq ($(DEBUG), 1)
	CFLAGS += -Wpedantic -O0 -g3
else
	CFLAGS += -Werror
endif

all: $(NAME)

-include $(DEPS)

bonus: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(BLUE)%s$(RESET): $(YELLOW)Building$(RESET) $(NAME)\n" $(NAME)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)%s$(RESET): $(MAGENTA)Compiling$(RESET) $<\n" $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) USE_ERRNO=1 --no-print-directory

clean:
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) object files\n" $(NAME)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) executables and libraries\n" $(NAME)
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean
	@make all --no-print-directory

.PHONY: all clean fclean re bonus $(LIBFT)
