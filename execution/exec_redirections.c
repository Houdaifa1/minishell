#include "../minishell.h"


int ft_handle_output(char *argument, int i)
{
    char *file_name;
    int j;
    int output_fd;

    file_name = ft_cpy_commande(argument, i + 1);
    while (argument[i + 1] && argument[i + 1] != '>' && argument[i + 1] != '<')
        i++;
    output_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (output_fd < 0)
    {
        perror(file_name);
        free(file_name);
        return (-1);
    }
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
    free(file_name);
    return (i);
}

int ft_handle_input(char *argument, int i)
{
    char *file_name;
    int j;
    int input_fd;

    file_name = ft_cpy_commande(argument, i + 1);
    while (argument[i + 1] && argument[i + 1] != '>' && argument[i + 1] != '<')
        i++;
    input_fd = open(file_name, O_RDONLY);
    if (input_fd < 0)
    {
        perror(file_name);
        free(file_name);
        return (-1);
    }
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
    free(file_name);
    return (i);
}
int ft_handle_append(char *argument, int i)
{
    char *file_name;
    int j;
    int append_fd;

    file_name = ft_cpy_commande(argument, i + 1);
    while (argument[i + 1] && argument[i + 1] != '>' && argument[i + 1] != '<')
        i++;
    append_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644  );
    if (append_fd < 0)
    {
        perror(file_name);
        free(file_name);
        return (-1);
    }
    dup2(append_fd, STDOUT_FILENO);
    close(append_fd);
    free(file_name);
    return (i);
}