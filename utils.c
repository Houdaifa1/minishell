#include "minishell.h"


t_data *creat_node(char *command, char **arguments)
{
	t_data	*new_node = malloc(sizeof(t_data));
	new_node->command = ft_strdup(command);
	new_node->argumment = arguments;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_node(t_data **head, char *command, char **arguments)
{
	t_data	*new_node;

	new_node = creat_node(command, arguments);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
}

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
				quote = 0;
		}
		else if (input[i] == ' ' && quote == 0)
		{
			while (input[i] == ' ')
				i++;
            if (input[i] == '\0')
                break;
			count++;
		}
		i++;
	}
	return (count + 1);
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
