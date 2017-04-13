# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 10:48:18 by pboutelo          #+#    #+#              #
#    Updated: 2017/03/03 17:24:30 by wolrajhti        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

NAME = libft.a

ECHO = echo
RED_L = \033[1;31m
GREEN_L = \033[1;32m
GREEN = \033[0;32m
BLUE = \033[1;34m
RED = \033[0;31m
GRAY = \033[1;30m
GRAY_L = \033[0;37m
CYAN = \033[0;36m
PURPLE_L = \033[1;35m
CYAN_L = \033[1;36m
NC = \033[0m

CC		= gcc
CFLAGS	= -Werror -Wall -Wextra
LFLAGS	=
IFLAGS	= -I./inc/

SRC_DIR	= ./src/
INC_DIR	= ./inc/
OBJ_DIR	= ./obj/

SRC_FILES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c \
ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c \
ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
ft_islower.c ft_isupper.c \
ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
ft_lstpushback.c ft_lstpushfront.c ft_lstat.c ft_lstsize.c ft_lstremif.c \
ft_get_next_line.c \
ft_printf.c \
ft_printf_directive.c ft_printf_loader.c ft_printf_tools.c \
ft_printf_writer_01.c ft_printf_writer_02.c ft_printf_writer_03.c \
ft_printf_parser_01.c ft_printf_parser_02.c \
ft_isnumberstr.c

OBJ_FILES = $(SRC_FILES:.c=.o)
INC_FILES = libft.h

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INC = $(addprefix $(INC_DIR), $(INC_FILES))

all: $(OBJ_DIR) $(NAME) auteur

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(ECHO) "\n$(BLUE)Linking library $(RED)$(NAME)$(BLUE).\n"
	$(AR) -rcs $@ $?
	@$(ECHO) "\t- $(GRAY)$(AR) -rcs $(RED)$(NAME)$(GRAY) object files:$(GREEN) OK! √\n$(BLUE)"
	ranlib $@
	@$(ECHO) "\t- $(GRAY)ranlib $(RED)$(NAME)$(GRAY) object files:$(GREEN) OK! √\n$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
	@$(ECHO) "$(BLUE)  - $(GRAY)Compiling: $(RED)$<$(GRAY) ... $(GREEN)OK! √$(NC)"

clean:
	@$(ECHO) "$(BLUE)  o $(GRAY)Removed $(RED)$(NAME) $(GRAY_L)object files$(GRAY).$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(ECHO) "$(BLUE)  o $(GRAY)Removed $(RED)$(NAME) $(GRAY_L)binary$(GRAY)."
	@rm -f $(NAME)

re: fclean all
