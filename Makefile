#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 22:49:10 by ciglesia          #+#    #+#              #
#    Updated: 2020/09/01 13:14:57 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	lem-in

INC			=	./include/
INC2		=	./libft/include/
INCLUDE		=	-I $(INC2) -I $(INC)
SUB_MAKE	=	./libft/
INC_LIB		=	-L$(SUB_MAKE) -lft

DIROBJ		=	./depo/
DIRSRC		=	./src/
DIRFARM		=	./src/farm/
DIRGRAPH	=	./src/graph/
DIRSOLVE	=	./src/solve/

SRC			=	lem_in.c
FARM		=	farm_treatment.c valid_input.c
GRAPH		=	graph_treatment.c attrib.c list.c print.c
SOLVE		=	solve.c valid_solution.c bfs.c bfs_treatment.c flow.c flow_treatment.c path_computation.c

OAUX		=	$(SRC:%=$(DIROBJ)%) $(FARM:%=$(DIROBJ)%) $(GRAPH:%=$(DIROBJ)%) $(SOLVE:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f

%.o		:		../$(DIRSRC)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRFARM)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRGRAPH)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRSOLVE)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

$(NAME)	: 		submake $(OBJS)
				@$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)

clean	:
				@$(RM) $(OBJS)
				@$(RM) $(DEPS)
				@(cd $(SUB_MAKE) && $(MAKE) clean)

all		:		$(NAME)

fclean	:		clean
				@$(RM) $(NAME)
				@(cd $(SUB_MAKE) && $(MAKE) fclean)

re		:		fclean $(NAME)
				@(cd $(SUB_MAKE) && $(MAKE) re)

submake	:
				@(cd $(SUB_MAKE) && $(MAKE))

.PHONY	: all clean fclean re
