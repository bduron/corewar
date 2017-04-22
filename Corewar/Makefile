# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bduron <bduron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 13:02:54 by bduron            #+#    #+#              #
#    Updated: 2017/04/22 18:00:51 by pboutelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR= corewar

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS	= -lncurses
LIBFT = -Llibft -lft -lncurses -lpthread

MKDIR= mkdir -p
RM= rm -rf

INC_DIR= includes/

SRC= \
corewar.c \
get_players.c \
get_players_errors.c \
vm_parsing.c \
vm_init_free.c \
load_arena.c \
vm_debbug.c \
vm_game.c \
operate.c \
operation_1.c \
operation_2.c \
operation_3.c \
operation_4.c \
op_shift.c \
op.c \
vw_draw_img.c \
vw_draw_life.c \
vw_draw_tools.c \
vw_init_win.c \
vw_init.c \
vw_maj_process.c \
vw_maj_win.c \
vw_th_anim.c \
vw_th_core.c \
vw_th_input.c \
vw_th_render.c \
vw_th_timer.c

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
	@$(CC) -o $@ $(CFLAGS) $(LFLAGS) $^ -I $(INC_DIR) $(LIBFT)
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
