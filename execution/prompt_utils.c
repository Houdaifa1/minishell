#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*home;
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

char *print_prompt(char **envp)
{
    char *home;
    char path[PATH_MAX];
    char *prompt;
	int i;

    getcwd(path, PATH_MAX);
	if (ft_strcmp(path, ft_getenv(envp, "HOME")) == 0)
		prompt = ft_strjoin("minishell :", "~");
	else
	{
		i = 0;
		home = ft_getenv(envp, "HOME");
		while(home && home[i] && path[i] && home[i] == path[i])
			i++;
		if (home && home[i] == '\0')
			prompt = ft_strjoin("minishell :~", &path[i]);
		else 
    		prompt = ft_strjoin("minishell :", path);
	}
    return(prompt);
}
