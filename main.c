#include "minishell.h"

char    **split_line_to_args(char *input)
{
    char    **args;
    int i;
    int j;
    char    quote;
    char    buffer[1024];
    int buf_index;

    i = 0;
    j = 0;
    quote = 0;
    buf_index = 0;
    args = malloc(sizeof(char *) * ft_count_args(input) + 1);
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
        else if (input[i] == ' ' && quote == 0 )
        {
            if (buf_index > 0)
            {
                buffer[buf_index] = '\0';
                args[j++] = ft_strdup(buffer);
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
        args[j++] = ft_strdup(buffer);
    }
    args[j] = NULL;
    return (args);
}

void  parse_line(t_data **data, char *input)
{
    char    *command;
    char    **arguments;
    char    *token;
    char    *remaining_input;
    int i;

    i = 0;
    if (check_qout(input) == 1)
    {
        printf("bash: syntax error\n");
        exit(1);
        //return ;
    }
    remaining_input = input;
    while ((token = strsplit_by_pipe(&remaining_input)) != NULL)
    {
        arguments = split_line_to_args(token);
        if (arguments[0] != NULL)
                ft_add_node(data, arguments);
    }
    // while (arguments[i] != NULL)
    // {
    //     free(arguments[i]);
    //     i++;
    // }
    // free(arguments);
}


void print_use_list(t_data *head)// for testing
{
    t_data *temp = head;
    int i = 0;
    while (temp)
    {
        while (temp->argumment[i] != NULL)
        {
            printf("Arg %d:%s\n", i, temp->argumment[i]);
            i++;
        }
        i = 0;
        temp = temp->next;
        if (temp)
        {
            printf("---- Next Command ----\n");
        }
    }
}

void ft_free_list(t_data *head)
{
    t_data *temp;
    int i;

    i = 0;
    while (head)
    {
        temp = head;
        head = head->next;
        // if (temp->argumment)
        // {
        //     while (temp->argumment[i] != NULL)
        //     {
        //         free(temp->argumment[i]);
        //         i++;
        //     }
        //     free(temp->argumment);
        //     i = 0;
        // }
        free(temp);
    }
}

int main()
{
    t_data  *data;
    char    *input;


    data = NULL;
    while (1)
    {
        input = readline("minishell $> ");
        if (input[0] != '\0')
        {
            parse_line(&data, input);
            add_history(input);
            exec_commands(data);
        }
        print_use_list(data);
        ft_free_list(data);
        data = NULL;
        free(input);
    }
}
