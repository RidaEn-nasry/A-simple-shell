

NAME = pipex


CFLAGS = -Wall -Wextra -Werror 
SRCS = ./srcs/main.c
INCS = -I./includes/

LIB_LIBFT_PATH = ../libft/
LIB_LIBFT = ../libft/libft.a
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@



all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB_LIBFT) -o $@ $(INCS) 

clean:
	@$(RM) $(OBJS)







