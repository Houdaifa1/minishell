#include "../minishell.h"

void ft_free_arr(char **paths)
{
    int i;

    i = 0;
    while(paths[i] != NULL)
    {
        free(paths[i]);
        i++;
    }
    free(paths);

}
int test_paths(char **commande, char **paths)
{
    int j;
    char *join;
    char *temp;

    if (execve(commande[0], commande, NULL) == -1)
    {
        j = 0;
        while(paths[j])
        {
            temp = ft_strjoin(paths[j], "/", 1, 1);
            join = ft_strjoin(temp, commande[0], 1, 1);
            free(temp);
            execve(join, commande, NULL);
            free(join);
            j++;
        }
    }
    return(1);
}
void exec_non_builtin(char **commande,t_env **envp, t_data **data, t_hold **hold_vars)
{
    int pid;
    char **paths;

    paths = ft_split(ft_getenv(*envp, "PATH"), ':');
    pid = fork();
    if (pid == 0)
    {
        if (test_paths(commande, paths) == 1)
            printf("%s: command not found\n", commande[0]);
        exit(0);
    }
    wait();
    ft_free_arr(paths);
}