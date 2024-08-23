NAME = minishell

SOURCE = main.c parsing/utils.c parsing/ft_free.c parsing/parsing.c execution/exec_comandes.c execution/exec_echo.c execution/exec_pwd.c execution/prompt_utils.c execution/exec_cd.c execution/exec_export.c

CFLAGS = -Wall -Wextra -Werror -w #-fsanitize=address 


all: $(NAME)

$(NAME): $(SOURCE)
	cc $(CFLAGS) $(SOURCE) -lreadline -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

