#include "../minishell.h"

char *grep_env_value(char *envp, int i)
{
    int j;
    char *value;

    j = 0;

    while (envp[j])
        j++;

    value = malloc(j - i + 1);
    j = 0;
    while (envp[i])
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
                break;
            i++;
        }
        if (var[i] == '\0' && envp[j][i] == '=')
            return (grep_env_value(envp[j], i + 1));
        j++;
    }
    return (NULL);
}
int go_home(char **commande, char **envp, char *home, char *join)
{
    int flag;

    flag = 1;
    home = getenv("HOME");
    if (commande[1] == NULL || (commande[1][0] == '-' && commande[1][1] == '-' && commande[1][2] == '\0'))
    {
        if (home == NULL)
            flag = 0;
        if (chdir(home) != 0)
            printf("%s : No such directory\n", home);
        flag = 0;
    }
    else if (commande[1][0] == '~')
    {
        if (home == NULL)
            flag = 0;
        join = ft_strjoin(home, &commande[1][1], 1, 1);
        if (chdir(join) != 0)
            printf("%s : No such directory\n", commande[1]);
        flag = 0;
    }
    // if (home != NULL)
    //     free(home);
    if (join != NULL)
        free(join);
    return (flag);
}

void exec_cd(char **commande, char **envp)
{
    char *old_pwd;
    int flag;

    if (commande[1] != NULL && commande[2] != NULL)
    {
        printf("too many arguments\n");
        return ;
    }
    flag = go_home(commande, envp, NULL, NULL);
    if (commande[1] != NULL && commande[1][0] == '-' && commande[1][1] == '\0')
    {
        old_pwd = ft_getenv(envp, "OLDPWD");
         //printf("MY_VAR=%s\n", old_pwd = getenv("OLDPWD"));
        if (old_pwd == NULL)
            return ;
        if (chdir(old_pwd) != 0)
            printf("%s : No such directory\n", old_pwd);
        return ;
    }
    if (flag == 1)
    {
        if (chdir(commande[1]) != 0)
            printf("%s : No such directory\n", commande[1]);
    }
}
