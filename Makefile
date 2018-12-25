NAME = EXE
CC = gcc -Wall -Werror -Wextra 
FILES = set_arg_by_type.o\
short_arg.o\
get_arguments.o\
int_arg.o\
cliarg.o\
string_arg.o\
syntax_check.o\
long_arg.o

all: $(NAME)

$(NAME): $(FILES)
	@$(CC) -o $@ $^ libft.a

.c.o:
	@$(CC) -c $<

clean:
	@/bin/rm -f $(FILES)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

allc: all clean
