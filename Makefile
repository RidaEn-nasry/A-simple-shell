

SRCS = ./mandatory/srcs/lexer/lexer.c\



LIBFT = ./mandatory/utils/libft/libft.a
LIBFT_PATH=./mandatory/utils/libft
CFLAGS = -Wall -Wextra -Werror
TARGET=minishell
LINK= -L/usr/lib -lreadline 
INC = -I/usr/local/include

OBJS = ${SRCS:.c=.o}

%.o: %.c 
		${CC} ${CFLAGS} -c -g $< -o $@
	

all: $(TARGET)

$(TARGET): ${OBJS}
	$(MAKE) -C $(LIBFT_PATH) 
	${CC} ${CFLAGS} ${LIBFT} ${INC} ${LINK} -o ${TARGET} ${OBJS}


clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	${RM} ${OBJS}

fclean: clean
	${RM} ${TARGET}
	${RM} ${LIBFT}

re: fclean all

.PHONY: all clean fclean re
	
