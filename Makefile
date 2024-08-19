NAME = minishell

SOURCE = main.c utils.c ft_split.c exec_comandes.c exec_echo.c exec_pwd.c prompt_utils.c exec_cd.c

CFLAGS = -Wall -Wextra -Werror -w # -fsanitize=address 


all: $(NAME)

$(NAME): $(SOURCE)
	cc $(CFLAGS) $(SOURCE) -lreadline -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

