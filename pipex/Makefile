# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 18:09:55 by vfranco-          #+#    #+#              #
#    Updated: 2022/10/07 16:42:53 by vfranco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	clang
FILES_PATH	=	src
FILES		=	pipex.c \
				pipes.c \
				processes.c \
				ft_split_pass.c \
				split_utils.c
OBJS_PATH	=	objs
OBJS		=	$(addprefix $(OBJS_PATH)/,$(notdir $(FILES:.c=.o)))
FLAGS		=	-Wall -Wextra -Werror
LIBFT_PATH	=	.dependencies/libft
LIBFT		=	$(LIBFT_PATH)/libft.a
RM			=	rm -f

###################################################################

all: $(OBJS_PATH) $(NAME)
	
$(OBJS_PATH):
				mkdir -p $(OBJS_PATH)

$(NAME):	$(OBJS) $(LIBFT)
				$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o pipex

$(OBJS_PATH)/%.o:	$(FILES_PATH)/%.c
				$(CC) -c $(FLAGS)  $< -o $(addsuffix .o, $(OBJS_PATH)/$(basename $(@F)))

$(LIBFT):
				make -C $(LIBFT_PATH)
				
clean:
				make clean -C $(LIBFT_PATH)
				$(RM) $(OBJS)

fclean:		clean
				make fclean -C $(LIBFT_PATH)
				$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
