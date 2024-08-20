#include "minishell.h"

void print_use_list(t_data *head) // for testing
{
    t_data *temp = head;
    int i = 0;
    while (temp)
    {
        while (temp->argumment[i] != NULL)
        {
            printf("Arg %d:%s\n", i, temp->argumment[i]);
            i++;
        }
        i = 0;
        temp = temp->next;
        if (temp)
        {
            printf("---- Next Command ----\n");
        }
    }
}

int main()
{
    t_data *data;
    char *input;

    data = NULL;
    while (1)
    {
        input = readline(print_prompt());
        if (input[0] != '\0')
        {
            if (parse_line(&data, input) == 0)
            {
                add_history(input);
                exec_commandes(data);  
            }
        }
        //print_use_list(data);
        ft_free_list(data); 
        data = NULL;
        free(input);
    }
}
