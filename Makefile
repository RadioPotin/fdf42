# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapinto<marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 16:47:44 by evogel            #+#    #+#              #
#    Updated: 2019/05/29 17:07:24 by dapinto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
COMP = $(CC) -c
DEBUG = $(CC) -g
NAME = fdf
NAMEDEB = fdfdeb
LIB = $(PATHLIB)libft.a -Lminilibx
LIBDEB= $(PATHLIB)libftdeb.a
BIN = ft_printf

INCLUDES += -Iincludes
INCLUDES += -Ilibft/includes -Iminilibx

DSYM += *.dSYM

MKDIR = mkdir -p
RMRF = rm -rf
MKE = make -C

INCS += fdf.h

#-PATHS && FLAGS-#

PATHINC = includes/
PATHOBJ = ./
PATHOBJDEB = .
PATHSRCS = srcs/
PATHLIB = libft/
PATHMAKE = libft/
vpath %.c srcs/
vpath %.h includes/
WFG = -Wall -Wextra -Werror
IFG = -I$(PATHINC)
CFG = $(WFG) $(IFG)
FDF = -lmlx_Linux -lm -lX11 -lXext

#-SRCS-#
SRCS += main.c
SRCS += reader.c
SRCS += miscellaneous.c
SRCS += alts_storer.c
SRCS += init.c
SRCS += mapper.c
SRCS += bresenham.c
SRCS += ft_event_manager.c
SRCS += ft_event_manager2.c
SRCS += color.c
SRCS += matrices.c

#-Printing-#
#No Color#
NO_COLOR    = \033[m
#Black#
BLACK       = \033[0;30m
#Red#
ERROR_COLOR = \033[0;31m
#Green#
OK_COLOR    = \033[0;32m
#Yellow#
WARN_COLOR  = \033[0;33m
#Blue#
BLUE        = \033[0;34m
#Purple#
COM_COLOR   = \033[0;35m
#Cyan#
OBJ_COLOR   = \033[0;36m
#White#
WHITE       = \033[0;37m

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
		printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	$(RM) $@.log; \
	exit $$RESULT
endef

OK_STRING    = "[DONE]"
ERROR_STRING = "[OHSHIT]"
WARN_STRING  = "[HOLDUP]"
COM_STRING   = "[PROJECT]"

#-RULES-#

OBJS = $(patsubst %.c, $(PATHOBJ)%.o, $(SRCS))
DEBOBJS = $(patsubst %.c, $(PATHOBJDEB)db%.o, $(SRCS))

all: $(NAME)

debug: $(PATHOBJDEB) $(NAMEDEB)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(WFG) -o $(NAME) $(SRCS) $(IFG) $(LIB) $(FDF) $(INCLUDES)

$(LIB): FORCE
	$(MKE) $(PATHMAKE)

$(OBJS): $(PATHOBJ)%.o : ./%.c $(INCS) Makefile
	$(call run_and_test, $(COMP) $(CFG) $(INCLUDES) $< -o $@)

$(NAMEDEB): $(LIBDEB) $(DEBOBJS)
	$(DEBUG) $(WFG) -o $(NAMEDEB) .db*.o $(IFG) $(LIBDEB) $(FDF) $(INCLUDES)

$(LIBDEB): FORCE
	$(MKE) $(PATHMAKE) debug

$(DEBOBJS): $(PATHOBJDEB)db%.o : %.c $(INCS) Makefile
	$(call run_and_test, $(DEBUG) -c $(CFG) $(INCLUDES) $(IFG) $< -o $@)

FORCE:

clean:
	@$(MKE) $(PATHMAKE) clean
	@$(RMRF) $(OBJS)
	@$(RMRF) *.o
	@$(RMRF) .db*.o
	@$(RMRF) $(DSYM)

fclean: clean
	@$(MKE) $(PATHMAKE) fclean
	@$(RMRF) $(NAME)
	@$(RMRF) $(NAMEDEB)
	@$(RMRF) $(BIN)

re: fclean all

.PHONY: clean fclean re debug all FORCE
