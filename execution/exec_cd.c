#include "../minishell.h"

char *grep_env_value(char *envp, int i)
{
    int j;
    char *value;

    j = 0;
   
    while(envp[j])
        j++;
    
    value = malloc (j - i + 1);
    j = 0;
    while(envp[i])
    {
        value[j] = envp[i];
        j++;
        i++;
    }
    value[j] = '\0';
    return (value);
}

char *ft_getenv(char **envp, char *var)
{
    int j;
    int i;

    j = 0;
    while (envp[j] != NULL)
    {
        i = 0;
        while (envp[j][i] && var[i])
        {
            if (envp[j][i] != var[i])
                break ;
            i++;
        }
        if (var[i] == '\0' && envp[j][i] == '=')
            return (grep_env_value(envp[j], i + 1));  
        j++;
    }
    return (NULL);
}


void exec_cd(char **commande, char **envp)
{
    char *home;
    char *join;

    home = ft_getenv(envp, "HOME");
    join = NULL;
    if (commande[1] == NULL || (commande[1][0] == '-' && commande[1][1] == '-' && commande[1][2] == '\0'))
    {
        if (home == NULL)
            return ;
        if (chdir(home) != 0)
            printf("%s : No such directory\n", home);
    }
    else if (commande[2] != NULL)
        printf("too many arguments\n");
    else if (commande[1][0] == '~')
    {
        if (home == NULL)
            return ;
        join = ft_strjoin(home, &commande[1][1], 1);
        if (chdir(join) != 0)
            printf("%s : No such directory\n", commande[1]);
    }
    else if (chdir(commande[1]) != 0)
        printf("%s : No such directory\n", commande[1]);
    if (home != NULL)
		free(home);
    if (join != NULL)
        free(join);
}
