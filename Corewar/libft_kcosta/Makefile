#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/02 10:00:00 by kcosta            #+#    #+#             *#
#*   Updated: 2017/02/18 15:19:40 by kcosta           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

# =========== Colors =========== #
CLEAR			:= "\033[2K"
UP				:= "\033[A"
EOC				:= "\033[0;0m"
BLACK			:= "\033[0;30m"
RED				:= "\033[0;31m"
GREEN			:= "\033[0;32m"
YELLOW			:= "\033[0;33m"
BLUE			:= "\033[0;34m"
PURPLE			:= "\033[0;35m"
CYAN			:= "\033[0;36m"
WHITE			:= "\033[0;37m"
# ============================== #

# ========== Editable ========== #
NAME			:= libft.a
# ============================== #

# ========== Standard ========== #
CC				:= gcc
FLAGS			:= -Wall -Wextra -Werror
# ============================== #

# =========== Files ============ #
SRCS_FILES		:=	string/ft_strcat.c			\
					string/ft_strclr.c			\
					string/ft_strchr.c			\
					string/ft_strdel.c			\
					string/ft_strswp.c			\
					string/ft_strcmp.c			\
					string/ft_strcpy.c			\
					string/ft_strequ.c			\
					string/ft_striter.c			\
					string/ft_strinsert.c		\
					string/ft_strremove.c		\
					string/ft_strdup.c			\
					string/ft_strlen.c			\
					string/ft_striteri.c		\
					string/ft_strlcat.c			\
					string/ft_strjoin.c			\
					string/ft_strmap.c			\
					string/ft_strncat.c			\
					string/ft_strmapi.c			\
					string/ft_strnequ.c			\
					string/ft_strncmp.c			\
					string/ft_strncpy.c			\
					string/ft_strnew.c			\
					string/ft_strrev.c			\
					string/ft_strrchr.c			\
					string/ft_strnstr.c			\
					string/ft_strsub.c			\
					string/ft_strstr.c			\
					string/ft_strrstr.c			\
					string/ft_strtrim.c			\
					string/ft_strepur.c			\
					string/ft_strsplit.c		\
					string/ft_strisalnum.c		\
					ctype/ft_isalnum.c			\
					ctype/ft_isascii.c			\
					ctype/ft_isblank.c			\
					ctype/ft_isdigit.c			\
					ctype/ft_isalpha.c			\
					ctype/ft_islower.c			\
					ctype/ft_isspace.c			\
					ctype/ft_isupper.c			\
					ctype/ft_toupper.c			\
					ctype/ft_tolower.c			\
					ctype/ft_isprint.c			\
					memory/ft_bzero.c			\
					memory/ft_memalloc.c		\
					memory/ft_memccpy.c			\
					memory/ft_memcpy.c			\
					memory/ft_memdel.c			\
					memory/ft_memchr.c			\
					memory/ft_memcmp.c			\
					memory/ft_memset.c			\
					memory/ft_memmove.c			\
					memory/ft_memdup.c			\
					utils/ft_atoi.c				\
					utils/ft_itoa.c				\
					utils/ft_getline.c			\
					utils/ft_getopt.c			\
					print/ft_printf_address.c	\
					print/ft_printf_check.c		\
					print/ft_printf.c			\
					print/ft_printf_char.c		\
					print/ft_printf_args.c		\
					print/ft_printf_pourcent.c	\
					print/ft_printf_octal.c		\
					print/ft_printf_hex.c		\
					print/ft_printf_str.c		\
					print/ft_putchar.c			\
					print/ft_putchar_fd.c		\
					print/ft_putendl.c			\
					print/ft_printf_wildcard.c	\
					print/ft_putendl_fd.c		\
					print/ft_putnbr_fd.c		\
					print/ft_putnbr.c			\
					print/ft_putnstr.c			\
					print/ft_putstr.c			\
					print/ft_putstr_fd.c		\
					print/ft_printf_unsigned.c	\
					print/ft_printf_num.c		\
					list/ft_lstadd.c			\
					list/ft_lstdelone.c			\
					list/ft_lstaddback.c		\
					list/ft_lstdel.c			\
					list/ft_lstiter.c			\
					list/ft_lstmap.c			\
					list/ft_lstnew.c			\
					tab/ft_tabdel.c				\
					tab/ft_tabstr.c				\
					tab/ft_tablen.c

HEADERS_FILES	:=	libft.h		\
					ft_string.h	\
					ft_ctype.h	\
					ft_memory.h	\
					ft_utils.h	\
					ft_print.h	\
					ft_list.h	\
					ft_tab.h
# ============================== #

# ========== Sources =========== #
SRCS_PATH		:= srcs/
SRCS			:= $(addprefix $(SRCS_PATH), $(SRCS_FILES))
# ============================== #

# ========== Objects =========== #
OBJS_PATH		:= objs/
OBJS_DIRS		:= $(addprefix $(OBJS_PATH), string/ ctype/ memory/ utils/ print/ list/ tab/)
OBJS			:= $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))
# ============================== #

# ========== Includes ========== #
INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
HEADERS			:= $(addprefix $(INCLUDES_PATH), $(HEADERS_FILES))
# ============================== #
#
.PHONY: all clean fclean re

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADER)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(OBJS_DIRS) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJS)
	@ar rc -v $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	@rm -fv $(OBJS)
	@rmdir $(OBJS_DIRS) 2> /dev/null || true
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NAME)

re: fclean all
