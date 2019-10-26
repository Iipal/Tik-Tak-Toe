# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 14:43:13 by tmaluh            #+#    #+#              #
#    Updated: 2019/10/26 14:20:53 by tmaluh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := bin/tiktaktoe
NPWD := $(CURDIR)/$(NAME)

CC_BASE := gcc -march=native -mtune=native

CC := $(CC_BASE) -Ofast -pipe -flto
CC_DEBUG := $(CC_BASE) -g3 -D DEBUG

CFLAGS := -Wall -Wextra -Werror -Wunused
IFLAGS := -I $(CURDIR)/includes

LIBSINC :=
LIBS :=

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBSINC += -I ~/.brew/include
	LIBS += -L ~/.brew/lib -rpath ~/.brew/lib
endif
LIBS += -lSDL2 -lSDL2_gfx -lm

SRCS := $(abspath $(wildcard srcs/*.c srcs/*/*.c srcs/*/*/*.c))
OBJ := $(SRCS:.c=.o)

DEL := rm -rf

WHITE := \033[0m
BGREEN := \033[42m
GREEN := \033[32m
RED := \033[31m
INVERT := \033[7m

SUCCESS := [$(GREEN)✓$(WHITE)]
SUCCESS2 := [$(INVERT)$(GREEN)✓$(WHITE)]

all: $(NAME)

$(OBJ): %.o: %.c
	@echo -e -n ' $@: '
	@$(CC) -c $(CFLAGS) $(LIBSINC) $(IFLAGS) $< -o $@
	@echo -e "$(SUCCESS)"

bin_dir:
	@mkdir -p bin

$(NAME): bin_dir $(OBJ)
	@echo -e -n ' <q.p> | $(NPWD): '
	@$(CC) $(OBJ) $(LIBS) -o $(NAME)
	@echo -e "$(SUCCESS2)"

del:
	@$(DEL) $(OBJ)
	@$(DEL) $(NAME)

pre: del all
	@echo -e "$(INVERT)$(GREEN)Successed re-build.$(WHITE)"

.PHONY: clear_pre
clear_pre:
	pre

set_cc_debug:
	@$(eval CC=$(CC_DEBUG))
debug_all: set_cc_debug pre
	@echo -e "$(INVERT)$(NAME) $(GREEN)ready for debug.$(WHITE)"
debug: set_cc_debug all
	@echo -e "$(INVERT)$(NAME) $(GREEN)ready for debug.$(WHITE)"

clean:
	@$(DEL) $(OBJ)

fclean: clean
	@$(DEL) $(NAME)
	@echo -e "$(INVERT)$(RED)deleted$(WHITE)$(INVERT): $(NPWD)$(WHITE)"

re: fclean all

norme:
	@echo -e "$(INVERT)norminette for $(GREEN)$(NAME)$(WHITE)$(INVERT):$(WHITE)"
	@norminette includes/
	@norminette $(SRCS)

.PHONY: re fclean clean all norme del pre debug debug_all
