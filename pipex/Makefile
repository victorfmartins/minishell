# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 18:09:55 by vfranco-          #+#    #+#              #
#    Updated: 2022/10/24 13:22:19 by asoler           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	clang
FILES_PATH	=	src
FILES		=	pipex.c \
				fd_utils.c \
				processes.c \
				ft_split_pass.c \
				split_utils.c \
				access_utils.c
OBJS_PATH	=	objs
OBJS		=	$(addprefix $(OBJS_PATH)/,$(notdir $(FILES:.c=.o)))
FLAGS		=	-Wall -Wextra -Werror
LIBFT_PATH	=	../libft
LIBFT		=	../libft.a
RM			=	rm -f

###################################################################

all: $(OBJS_PATH) $(NAME)
	
$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -g3 $(OBJS) $(LIBFT) -o pipex

$(OBJS_PATH)/%.o:	$(FILES_PATH)/%.c
	$(CC) -c -g3 $(FLAGS)  $< -o $(addsuffix .o, $(OBJS_PATH)/$(basename $(@F)))

$(LIBFT):
	make -C $(LIBFT_PATH)

bonus: all

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
