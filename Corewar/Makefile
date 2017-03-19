# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bduron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 13:02:54 by bduron            #+#    #+#              #
#    Updated: 2017/03/09 17:23:17 by bduron           ###   ########.fr        #
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
