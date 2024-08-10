#include "minishell.h"

// int	count_args(char *input)
// {
// 	int	count;
// 	int	i;
// 	char	quote;

// 	count = 0;
// 	i  = 0;
// 	quote = 0;
// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 		{
// 			if (quote == 0)
// 				quote = input[i];
// 			else if (quote == input[i])
// 				quote = 0;
// 		}
// 		else if (input[i] == ' ' && quote == 0)
// 			count++;
// 		i++;
// 	}
// 	return (count + 1);
// }

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
