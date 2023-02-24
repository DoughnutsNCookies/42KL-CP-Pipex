# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/09/21 14:14:56 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
LIBFT		=	libft.a
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
SRCS_FILES	=	pipex_main_bonus \
				pipex_fails_bonus \
				pipex_file_bonus \
				pipex_produce_bonus
SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
SRCS_DIR	=	srcs/
LIBFT_DIR	=	libft
OBJS_DIR	=	objs/

all:			
				mkdir -p $(OBJS_DIR)
				make libft
				make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(LIBFT_DIR)/$(LIBFT) $(OBJS) -o $(NAME)

bonus:			
				make $(NAME)

libft:
				make -C $(LIBFT_DIR)

clean:
				rm -rf $(OBJS_DIR)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all bonus libft clean fclean re
