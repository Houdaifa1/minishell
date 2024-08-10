#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int	count_args(char *input)
{
	int	count;
	int	i;
	char	quote;

	count = 0;
	i  = 0;
	quote = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == ' ' && quote == 0)
			count++;
		i++;
	}
	return (count + 1);
}

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
    args = malloc(sizeof(char *) * count_args(input) + 1);
    while (input[i] != '\0')
    {
        while (input[i + 1] == ' ' && quote == 0)
            i++;
        if (input[i] == '\'' || input[i] == '"')
        {
            if (quote == 0)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
        }
        else if (input[i] == ' ' && quote == 0)
        {
            buffer[buf_index] = '\0';
            args[j++] = ft_strdup(buffer);
            buf_index = 0;
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
    char*command;
    char    **arguments;
    int i = 0;

    arguments = split_line_to_args(input);
    while (arguments[i] != NULL)
    {
        printf("%s ", arguments[i]);
        i++;
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
        }
        else
            free(input);
    }
}
