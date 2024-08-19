#include "minishell.h"


int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return(s1[i] - s2[i]);
}

void exec_simple_commande(t_data *commande)
{
    if (ft_strcmp(commande->argumment[0], "echo") == 0)
        exec_echo(commande->argumment);
    else if (ft_strcmp(commande->argumment[0], "pwd") == 0)
        exec_pwd();
    else if (ft_strcmp(commande->argumment[0], "cd") == 0)
        exec_cd(commande->argumment);
}
void exec_commandes(t_data *commandes)
{
    
    if (commandes->next == NULL)
        exec_simple_commande(commandes);
}