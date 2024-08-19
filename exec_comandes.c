#include "minishell.h"


int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return(s1[i] - s2[i]);
}

void exec_simple_commande(t_data *commande)
{
    if (ft_strcmp(commande->argumment[0], "echo") == 0)
        exec_echo(commande->argumment);
}
void exec_commands(t_data *commandes)
{
    if (commandes->next == NULL)
        exec_simple_commande(commandes);
}