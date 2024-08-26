#include "../minishell.h"

int x = 0;

char **ft_environment_variables(char **arguments, t_env *env_var)
{
    int i;
    int f;
    int j;
    int n;
    char *result;
    char tmp[BUFSIZ];
    char *env;
    char str[2];

    i = 0;
    while (arguments[i] != NULL)
    {
        f = 0;
        j = 0;
        n = 0;
        result = NULL;
        while (arguments[i][f] != '\0')
        {
            if (arguments[i][f] == '$' && ft_is_digits(arguments[i][f + 1]) == 1)
                f = f + 2;
            else if (arguments[i][f] == '$' && arguments[i][f + 1] != '$' && x != 1 && arguments[i][f + 1] != '\0')
            {
                f++;
                j = 0;
                while (arguments[i][f] != '\0' && arguments[i][f] != ' ' && ft_is_valid(arguments[i][f]) == 1 && arguments[i][f] != '$' && j < sizeof(tmp) - 1)
                {
                    tmp[j] = arguments[i][f];
                    j++;
                    f++;
                }
                tmp[j] = '\0';
                env = ft_getenv(env_var, tmp);
                if (env != NULL)
                {
                    result = ft_strjoinee(result, env);
                }
            }
            else
            {
                str[0] = arguments[i][f];
                str[1] = '\0';
                result = ft_strjoinee(result, str);
                f++;
            }
        }
        free(arguments[i]);
        arguments[i] = result;
        i++;
    }

    return arguments;
}   

int    ft_check(char *input)
{
    int i;

    i = 0;
    if (input[i])
    {
        while (input[i] == ' ')
            i++;
        if ((input[i] == '\'' || input[i] == '\"' ) && (input[i + 1] == '\'' || input[i + 1] == '\"'))
        {
            if (input[i + 2] == '\0' || input[i + 2] == ' ')
                return (0);
        }
    }
    return (1);
}

char **split_line_to_args(char *input)
{
    char **args;
    int i;
    int j;
    char quote;
    char buffer[1024];
    int buf_index;
    int check;
    int h;

    i = 0;
    j = 0;
    h = 0;
    quote = 0;
    buf_index = 0;
    args = malloc(sizeof(char *) * (ft_count_args(input) + 1));
    if (!args)
        return (NULL);
    check = ft_check(input);
    while (input[i] != '\0')
    {
        if ((input[i] == '\'' || input[i] == '"') && (input[i] == quote || quote == 0) && check == 1)
        {
            if (input[i] == '\"')
                x = 0;
            else
                x = 1;
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
    if (buf_index ==  0)
    {
        args[1] == NULL; 
    }
    args[j] = NULL;
    return (args);
}

int  parse_line(t_data **data, char *input, t_env *env_var)
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
        return (1);
    }
    remaining_input = input;
    while ((token = strsplit_by_pipe(&remaining_input)) != NULL)
    {
        arguments = split_line_to_args(token);
        arguments = ft_environment_variables(arguments, env_var);
        if (arguments[0] != NULL)
            ft_add_node(data, arguments);
        else
            return (1);
    }
    return (0);
}
