# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 16:12:01 by ren-nasr          #+#    #+#              #
#    Updated: 2022/06/06 18:03:10 by ren-nasr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./mandatory/srcs/lexer/lexer.c\
		./mandatory/srcs/lexer/errors.c\
		./mandatory/srcs/lexer/utils_00.c\
		./mandatory/srcs/lexer/utils_01.c\
		./mandatory/srcs/lexer/states.c\
		./mandatory/srcs/lexer/handlers/handle_cmd.c\
		./mandatory/srcs/lexer/handlers/delim_in.c\
		./mandatory/srcs/lexer/handlers/delim_in_help.c\
		./mandatory/srcs/lexer/handlers/handle_env.c\
		./mandatory/srcs/lexer/handlers/append_out.c\
		./mandatory/srcs/lexer/handlers/append_out_help.c\
		./mandatory/srcs/lexer/handlers/handle_quote.c\
		./mandatory/srcs/lexer/handlers/handle_args.c\
		./mandatory/srcs/lexer/handlers/handle_exe.c\
		./mandatory/srcs/executor/executor.c\
		./mandatory/srcs/executor/builtins.c\
		./mandatory/srcs/executor/commands/cd.c\
		./mandatory/srcs/executor/commands/echo.c\
		./mandatory/srcs/executor/commands/env.c\
		./mandatory/srcs/executor/commands/exit.c\
		./mandatory/srcs/executor/commands/pwd.c\
		./mandatory/srcs/executor/commands/unset.c\
		./mandatory/srcs/executor/commands/export.c\
		./mandatory/srcs/executor/exe_handle_cmd.c\
		./mandatory/srcs/executor/exe_handle_out.c\
		./mandatory/srcs/executor/exe_handle_app.c\
		./mandatory/srcs/executor/exe_handle_in.c\
		./mandatory/srcs/executor/exe_handle_heredoc.c\

LIBFT = ./mandatory/utils/libft/libft.a

LIBFT_PATH=./mandatory/utils/libft

CFLAGS = -Wall -Wextra -Werror -g

TARGET=minishell

LINK= §-L/opt/homebrew/Cellar/readline/8.1.2/lib/ -L/opt/homebrew/Cellar/readline/8.1.2/lib/ -lreadline


INC = -I/usr/local/include 

OBJS = ${SRCS:.c=.o}

OBJS_TESTS = ${SRCS_TESTS:.c=.o}

INCL_CHECK = -I/opt/homebrew/Cellar/check/0.15.2/include/

LIB_CHECK = -L/opt/homebrew/Cellar/check/0.15.2/lib/ -lcheck

INCS = -I./mandatory/includes/ 


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
	
