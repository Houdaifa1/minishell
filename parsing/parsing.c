#include "../minishell.h"

char **split_line_to_args(char *input)
{
    char **args;
    int i;
    int j;
    char quote;
    char buffer[1024];
    int buf_index;

    i = 0;
    j = 0;
    quote = 0;
    buf_index = 0;
    args = malloc(sizeof(char *) * (ft_count_args(input) + 1));
    if (!args)
        return (NULL);
    while (input[i] != '\0')
    {
        if ((input[i] == '\'' || input[i] == '"') && (input[i] == quote || quote == 0))
        {
            if (quote == 0)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        else if (input[i] == ' ' && quote == 0)
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                args[j++] = strdup(buffer);
                buf_index = 0;
            }
            while (input[i] == ' ')
                i++;
            if (input[i] == '\0')
                break;
            i--;
        }
        else
            buffer[buf_index++] = input[i];
        i++;
    }
    if (buf_index > 0)
    {
        buffer[buf_index] = '\0';
        args[j++] = strdup(buffer);
    }
    args[j] = NULL;
    return (args);
}

int  parse_line(t_data **data, char *input)
{
    char *command;
    char **arguments;
    char *token;
    char *remaining_input;
    int i;

    i = 0;
    if (check_qout(input) == 1)
    {
        printf("minishell: syntax error\n");
        //exit(1);
        return (1);
    }
    remaining_input = input;
    while ((token = strsplit_by_pipe(&remaining_input)) != NULL)
    {
        arguments = split_line_to_args(token);
        if (arguments[0] != NULL)
            ft_add_node(data, arguments);
    }
    return (0);
}
