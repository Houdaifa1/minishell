#include "minishell.h"

void exec_cd(char **commande)
{
    char *home;

    if (commande[2] != NULL)
        printf("too many arguments\n");
    // if (commande[1] == NULL)
    // {
    //     home = getenv("home");
    //     printf("    sdsd   %s\n", home);
    //     if (chdir(home) != 0)
    //         printf("%s : No such directory\n", commande[1]);
    // }
    else if (chdir(commande[1]) != 0)
        printf("%s : No such directory\n", commande[1]);
}