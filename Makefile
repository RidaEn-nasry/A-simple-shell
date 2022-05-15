# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 16:12:01 by ren-nasr          #+#    #+#              #
#    Updated: 2022/05/14 09:58:51 by ren-nasr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./mandatory/srcs/lexer/lexer.c\
		./mandatory/srcs/lexer/errors.c\
		./mandatory/srcs/lexer/utils.c\
		./mandatory/srcs/lexer/handlers/cmds.c\
		./mandatory/srcs/lexer/handlers/delim_in.c\
		./mandatory/srcs/lexer/handlers/env.c\
		./mandatory/srcs/lexer/handlers/append_out.c\
		./mandatory/srcs/lexer/handlers/quote.c



LIBFT = ./mandatory/utils/libft/libft.a
LIBFT_PATH=./mandatory/utils/libft
CFLAGS = -Wall -Wextra -Werror -g
TARGET=minishell
LINK= -L/usr/lib -lreadline 


INC = -I/usr/local/include

OBJS = ${SRCS:.c=.o}

# tests stuff 
SRCS_TESTS = ./tests/main.c\
			./tests/lexer_tests/handle_app_tests.c

OBJS_TESTS = ${SRCS_TESTS:.c=.o}

INCL_CHECK = -I/opt/homebrew/Cellar/check/0.15.2/include/
LIB_CHECK = -L/opt/homebrew/Cellar/check/0.15.2/lib/ -lcheck
INCS = -I./mandatory/includes/

#end of tests stuff

%.o: %.c 
		${CC} ${CFLAGS} ${INCL_CHECK} ${INCS} -c $< -o $@
	

all: $(TARGET)

$(TARGET): ${OBJS}
	$(MAKE) -C $(LIBFT_PATH) 
	${CC} ${CFLAGS} ${LIBFT} ${INC} ${LINK} -o ${TARGET} ${OBJS}

check : ${OBJS_TESTS} ${OBJS}
	${MAKE} -C $(LIBFT_PATH)
	${CC} $(LIBFT) ${CFLAGS} ${LINK} ${LIB_CHECK} -o check ${OBJS_TESTS} ${OBJS} 

clean:
		$(MAKE) -C $(LIBFT_PATH) clean
		${RM} ${OBJS}

fclean: clean
	${RM} ${TARGET}
	${RM} ${LIBFT}

re: fclean all

.PHONY: all clean fclean re
	
