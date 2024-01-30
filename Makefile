# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdenis <jdenis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 21:05:04 by dlacuey           #+#    #+#              #
#    Updated: 2024/01/30 18:22:31 by dlacuey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

LDFLAGS = $(LIBFT) -lreadline

CPPFLAGS =																	\
																			\
				-I includes/philo.h											\
																			\

OBJS =																		\
																			\
				libft_func.o												\
				check_arguments_validity.o									\
				prepare_the_table.o											\
				get_time.o													\
				clean_the_table.o											\
				print_message.o												\
				start_the_dinner.o											\
				routine.o													\
				ft_usleep.o													\
				main.o														\
																			\

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
