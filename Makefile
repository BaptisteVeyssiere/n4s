##
## Makefile for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
##
## Made by Baptiste veyssiere
## Login   <VEYSSI_B@epitech.net>
##
## Started on  Tue May 24 16:26:39 2016 Baptiste veyssiere
## Last update Wed May 25 09:55:22 2016 ilyas semmaoui
##

NAME	= ia

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Werror -Wall -Wextra -ansi -pedantic -Iinclude

MKDIR	= mkdir -p

SRCDIR	= src

OBJDIR	= obj

SRC	= src/main.c		\
	src/info_lidar.c	\
	src/get_next_line.c	\
	src/my_getdouble.c	\
	src/my_memset.c		\
	src/verif_command.c

OBJ	= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@echo "Linkage complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
