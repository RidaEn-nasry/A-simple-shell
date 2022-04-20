

NAME = pipex


CFLAGS = -Wall -Wextra -Werror -g 
SRCS = ./srcs/main.c
INCS = -I./includes/

LIB_LIBFT_PATH = ../libft/
LIB_LIBFT = ../libft/libft.a
GNL = ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c



OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB_LIBFT) $(GNL) -o $@ $(INCS) 

clean:
	@$(RM) $(OBJS)




