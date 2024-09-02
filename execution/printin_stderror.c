#include "../minishell.h"


void ft_putchar_fd(char c)
{
    write(2, &c, 1);
}
void	ft_putstr_fd(char const *str)
{
	while (*str)
		ft_putchar_fd(*str++);
}