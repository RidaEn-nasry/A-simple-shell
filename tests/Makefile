

# get args from make --arg


LIBFT_TEST = /Users/wa5ina/42/minishell/mandatory/utils/libft/
LIBFT = libft.a

INCL = -I/opt/homebrew/Cellar/check/0.15.2/include/
LIB = -L/opt/homebrew/Cellar/check/0.15.2/lib/ -lcheck


src= ./main.c\
	./libft_tests.c \


test: $(src)
	$(MAKE) -C $(LIBFT_TEST)
	gcc -Wall -Wextra -Werror -o test $(src) $(LIB) $(LIBFT_TEST)/$(LIBFT) $(INCL)





.PHONY: test 
