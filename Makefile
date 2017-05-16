# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/19 14:14:34 by jecarol           #+#    #+#              #
#    Updated: 2017/05/10 20:07:32 by jecarol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS_LIST = main.c ft_minishell.c exec.c ft_cd.c ft_env_mngmnt.c\
 			ft_exit.c ft_echo.c ft_error.c  ft_env.c env_misc.c ft_set_unset.c
SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = objs/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

HEADERS = -I./libft -I./includes

LIB = -L./libft -lft

# COLOR
C_GOOD = "\033[32m"
C_DURING = "\033[36m"

# MESSAGE
SUCCESS = $(C_GOOD)COMPILATION SUCCEEDED

all: $(NAME)

$(NAME): $(OBJS)
	@make re -C ./libft/
	@echo $(C_DURING)"Compiling" [ $(NAME) . . . ]
	@$(CC) $(CFLAGS) $^ $(LIB) -o $@
	@echo $(SUCCESS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
		@/bin/rm -rf $(OBJS_DIR) $(NAME).dSYM
		@make clean -C libft/
		@echo $(C_GOOD)"OBJ FILES && DEBUG FOLDER DELETED"

fclean: clean
		@/bin/rm -rf $(NAME)
		@make fclean -C libft/
		@echo $(C_GOOD)"EXECUTABLE FILE DELETED"

re: fclean all
