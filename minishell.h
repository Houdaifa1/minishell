#ifndef MINISHELL_H
# define    MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

typedef struct echo
{
    char    **argumment;
    struct data *next;
}   t_data;

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
int	ft_count_args(char *input);
void	ft_add_node(t_data **head, char **arguments);
t_data *creat_node(char **arguments);
char *strsplit_by_pipe(char **str);
int check_qout(char *input);
void    exec_commandes(t_data *commandes);
void    exec_echo(char **commande);
void    ft_putstr(char *str);
void exec_pwd();
char *print_prompt();

#endif