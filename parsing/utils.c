#include "../minishell.h"

t_data *creat_node(char **arguments)
{
	t_data	*new_node = malloc(sizeof(t_data));
    if (!new_node)
        return NULL;
	new_node->argumment = arguments;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_node(t_data **head, char **arguments)
{
	t_data	*new_node;
	t_data	*tmp = *head;

	new_node = creat_node(arguments);
    if (!new_node)
        return;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

// t_data *creat_node(char **arguments)
// {
//     t_data *new_node = malloc(sizeof(t_data));
//     if (!new_node)
//         return NULL;
//     static int i = 0;
//     // Initialize the struct fields
//     new_node->argumment = arguments;
//     if  (i == 0)
//     {
//         new_node->input_files = NULL;
//         new_node->output_files = NULL;
//         new_node->append_output_files = NULL;
//         new_node->here_document = NULL;
//     }
//     i = 1;
//     new_node->next = NULL;

//     // // Check for redirections within arguments and set the fields accordingly
//     // for (int i = 0; arguments[i] != NULL; i++)
//     // {
//     //     if (strcmp(arguments[i], "<") == 0 && arguments[i + 1] != NULL)
//     //     {
//     //         new_node->input_files[i] = ft_strdup(arguments[i + 1]);
//     //         // Shift arguments to remove redirection symbol and file
//     //         for (int j = i; arguments[j] != NULL; j++)
//     //             arguments[j] = arguments[j + 2];
//     //         i--; // Adjust index since arguments were shifted
//     //     }
//     //     else if (strcmp(arguments[i], ">") == 0 && arguments[i + 1] != NULL)
//     //     {
//     //         new_node->output_files[i] = ft_strdup(arguments[i + 1]);
//     //         for (int j = i; arguments[j] != NULL; j++)
//     //             arguments[j] = arguments[j + 2];
//     //         i--;
//     //     }
//     //     else if (strcmp(arguments[i], ">>") == 0 && arguments[i + 1] != NULL)
//     //     {
//     //         new_node->append_output_files[i] = ft_strdup(arguments[i + 1]);
//     //         for (int j = i; arguments[j] != NULL; j++)
//     //             arguments[j] = arguments[j + 2];
//     //         i--;
//     //     }
//     //     else if (strcmp(arguments[i], "<<") == 0 && arguments[i + 1] != NULL)
//     //     {
//     //         new_node->here_document = ft_strdup(arguments[i + 1]);
//     //         for (int j = i; arguments[j] != NULL; j++)
//     //             arguments[j] = arguments[j + 2];
//     //         i--;
//     //     }
//     // }
//     return new_node;
// }


int	ft_count_args(char *input)
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
			{
				quote = 0;
			}
			i++;
		}
		else if (input[i] == ' ' && quote == 0)
		{
			while (input[i] == ' ')
				i++;
            if (input[i] == '\0')
                break;
			count++;
		}
		else
			i++;
	}
	return (count + 1);
}

int check_qout(char *input)
{
    int i;
    int flag;
    int quote;
	int	count;

    i = 0;
    flag = 0;
    quote = 0;
	count = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            if (quote == 0)
            {
                quote = input[i];
                flag = 1;
            }
            else if (quote == input[i])
            {
                quote = 0;
                flag = 0;
            }
        }
		else if (input[i] == '|' && quote == 0)
		{
			if (input[i] == '|' && input[i + 1] == '|')
				return (1);
		}
        i++;
    }
    return (flag);
}

char *strsplit_by_pipe(char **str)
{
    char	*start;
    char	*pipe_pos;
    char	quote;
    int	i;

	start = *str;
	pipe_pos = NULL;
	quote = 0;
	i = 0;
    if (start == NULL)
        return NULL;
    while (start[i] != '\0')
    {
        if (start[i] == '\'' || start[i] == '"')
        {
            if (quote == 0)
                quote = start[i];
            else if (quote == start[i])
                quote = 0;
        }
        else if (start[i] == '|' && quote == 0)
        {
            pipe_pos = &start[i];
            break;
        }
        i++;
    }
    if (pipe_pos != NULL)
    {
        *pipe_pos = '\0';
        *str = pipe_pos + 1;
    }
    else
        *str = NULL;
    return (start);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		j;
	char	*dup;

	dup = malloc ((ft_strlen(s1) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		dup[j] = s1[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

// void parse_redirections(t_data *command, char **tokens) {
//     int i = 0;

//     while (tokens[i] != NULL)
//     {
//         if (strcmp(tokens[i], "<") == 0)
//         {
//             if (tokens[i + 1] != NULL)
//             {
//                 command->input_file = strdup(tokens[i + 1]);  // Store the input file
//                 // Shift tokens left by two positions to remove redirection operator and file name
//                 for (int j = i; tokens[j] != NULL; j++)
//                 {
//                     tokens[j] = tokens[j + 2];
//                 }
//             }
//         }
//         else if (strcmp(tokens[i], ">") == 0)
//         {
//             if (tokens[i + 1] != NULL)
//             {
//                 command->output_file = strdup(tokens[i + 1]);  // Store the output file
//                 // Shift tokens left by two positions to remove redirection operator and file name
//                 for (int j = i; tokens[j] != NULL; j++) {
//                     tokens[j] = tokens[j + 2];
//                 }
//             }
//         }
//         else if (strcmp(tokens[i], ">>") == 0)
//         {
//             if (tokens[i + 1] != NULL) {
//                 command->append_output_file = strdup(tokens[i + 1]);  // Store the append output file
//                 // Shift tokens left by two positions to remove redirection operator and file name
//                 for (int j = i; tokens[j] != NULL; j++) {
//                     tokens[j] = tokens[j + 2];
//                 }
//             }
//         }
//         else if (strcmp(tokens[i], "<<") == 0)
//         {
//             if (tokens[i + 1] != NULL)
//             {
//                 command->here_document = strdup(tokens[i + 1]);  // Store the here-document delimiter
//                 // Shift tokens left by two positions to remove redirection operator and delimiter
//                 for (int j = i; tokens[j] != NULL; j++) {
//                     tokens[j] = tokens[j + 2];
//                 }
//             }
//         }
//         else
//             i++;  // Move to the next token
//     }
// }