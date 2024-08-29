#include "../minishell.h"

int x = 0;

int ft_check_exp(char *str)
{
    if (str[0] == '$' && x == 1)
    {
        x = 0;
        return (1);
    }
    else
        return (0);
}

char *ft_environment_variables(char *arguments, t_env *env_var)
{
    int i;
    int j;
    char *result;
    char tmp[BUFSIZ];
    char *env;
    char str[2];

    i = 0;
    j = 0;
    result = NULL;
    while (arguments[i] != '\0')
    {
        if (arguments[i] == '$' && ft_is_digits(arguments[i + 1]) == 1)
            i = i + 2;
        else if (arguments[i] == '$' && arguments[i + 1] != '$' && ( x == 0 || x == 2) && arguments[i + 1] != '\0')
        {
            i++;
            j = 0;
            while (arguments[i] != '\0' && arguments[i] != ' ' && ft_is_valid(arguments[i]) == 1 && arguments[i] != '$' && j < sizeof(tmp) - 1)
            {
                tmp[j] = arguments[i];
                j++;
                i++;
            }
            tmp[j] = '\0';
            env = ft_getenv(env_var, tmp);
            if (env != NULL)
                result = ft_strjoinee(result, env);
            else if (env == NULL && x != 2)
                result = ft_strjoinee(result, "");
        }
        else
        {
           
            str[0] = arguments[i];
            str[1] = '\0';
            result = ft_strjoinee(result, str);
            i++;
        }
    }
    if (result == NULL)
    {
        arguments = NULL;
        return (arguments);
    }
    else
    {
        if (result != NULL)
            arguments = result;
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

char **split_line_to_args(char *input,  t_env *env_var)
{
    char **args;
    char    *env;
    int i;
    int j;
    char quote;
    char buffer[1024];
    int buf_index;
    int check;

    i = 0;
    j = 0;
    quote = 0;
    buf_index = 0;
    args = malloc(sizeof(char *) * (ft_count_args(input) + 1));
    if (!args)
        return (NULL);
    check = ft_check(input);
    while (input[i] != '\0')
    {
        if ((input[i] == '\"' && input[i + 1] == '\"' ) && (input[i + 2] != '\"' || input[i + 2] == '\0') && (input[i + 2] == ' ' || input[i + 2] == '\0')  && quote == 0 && buf_index == 0)
        {
            args[j] = ft_strdup("");
            j++;
            i = i + 2;
        }
        if ((input[i] != '\'' && input[i] != '"') && quote == 0 && buf_index == 0)
            x = 2;
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
                env = ft_environment_variables(buffer, env_var);
                if (env != NULL)
                    args[j++] = ft_strdup(env);
                if (env != NULL)
                    free(env);
                buf_index = 0;
                x = 0;
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
        env = ft_environment_variables(buffer, env_var);
        if (env != NULL)
            args[j++] = ft_strdup(env);
        if (env != NULL)
            free(env);
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
        arguments = split_line_to_args(token, env_var);
        if (arguments[0] != NULL)
            ft_add_node(data, arguments);
        else
            return (1);
    }
    return (0);
}
