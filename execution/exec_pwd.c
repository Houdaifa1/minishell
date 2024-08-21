#include "../minishell.h"

void exec_pwd(char **commande)
{
    if (commande[1] != NULL && commande[1][0] == '-' &&  commande[1][1] != '\0')
    {
        if (commande[1][1] != '-' || commande[1][2] != '\0')
        {
            printf("pwd takes no option\n");
            return ;
        }
    }
    char path[PATH_MAX];

    getcwd(path, PATH_MAX);
    printf("%s\n", path);
}
