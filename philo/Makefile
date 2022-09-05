# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrings <hrings@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 08:58:57 by hrings            #+#    #+#              #
#    Updated: 2022/05/20 11:48:03 by hrings           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread

OBJDIR = build/
HEADER = .
SRCS := main.c utilities.c error.c run_dinner.c active_phil.c \
		printer.c clean_up.c checker.c time.c action.c init_philo.c

OBJECTS := $(SRCS:.c=.o)
OBJECTS_PREFIXED := $(addprefix $(OBJDIR), $(OBJECTS))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re test

all: $(NAME)

test: CFLAGS+= -fsanitize=thread -g

test: re

$(NAME): $(OBJECTS_PREFIXED) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJECTS_PREFIXED) -I$(HEADER) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_PREFIXED): build/%.o : %.c
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN).$(RESET)\c"
	$(CC) $(CFLAGS) -c  $< -o $@ -I$(HEADER)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(NAME): $(RED)object files and directory were deleted$(RESET)"

fclean: clean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)Cleared all were deleted$(RESET)"

re: fclean all
