# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bduron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 13:02:54 by bduron            #+#    #+#              #
#    Updated: 2017/03/28 16:38:06 by cpoulet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR= corewar

CC= gcc
CFLAGS= -Wall -Wextra -Werror -g -fsanitize=address
LIBFT= -Llibft -lft 

MKDIR= mkdir -p
RM= rm -rf

INC_DIR= includes/

SRC= \
corewar.c \
get_players.c \
get_players_errors.c \
vm_init_free.c \
load_arena.c \
vm_debbug.c \
vm_game.c \
operate.c \
operation_1.c \
operation_2.c \
operation_3.c \
operation_4.c \
op.c


OBJ= $(SRC:.c=.o)

VPATH= srcs/corewar

########################
#    Makefile rules    # 
########################

all: libft $(COREWAR)

libft:
	@make -C libft

# Executables 

$(COREWAR): $(OBJ)
	@$(CC) -o $@ $(CFLAGS) $^ -I $(INC_DIR) $(LIBFT) 
	@echo "Compiling [$@]"

# Object files 

$(OBJ): $(SRC)
	@$(CC) -c $^ $(CFLAGS) -I $(INC_DIR) 
	@echo "Compiling [$^]"

# Cleaning rules 

clean:
	@rm -f $(OBJ)
	@echo "Cleaning [$(OBJ)]"	

fclean: clean
	@rm -rf $(COREWAR)
	@make fclean -C libft
	@echo "Cleaning [libft corewar]"	

re: fclean all

.PHONY: clean fclean re libft 
