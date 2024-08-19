#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 4);
	if (!join)
		return (NULL);
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
    join[i] = '$';
    join[i + 1] = '>';
	join[i + 2] = ' ';
	join[i + 3] = '\0';
	return (join);
}
char *print_prompt()
{
    char *join;
    char path[PATH_MAX];
    char *prompt;

    getcwd(path, PATH_MAX);
    prompt = ft_strjoin("minishell :", path);
    return(prompt);
}