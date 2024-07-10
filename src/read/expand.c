#include <minishell.h>

void	expand_var(t_data *data, int pos)
{
	char	*temp;

	temp = data->list->args[pos];
	data->list->args[pos] = getenv(&data->commands[pos][1]);
	free(temp);
}

 void	expansor(t_data *data)
 {
 	int i;
    int j;

 	i = 0;
    j = 0;
 	while (data->list->args && data->list->args[i])
 	{
        while (data->list->args[i][j])
        {
            if ()
            j++;
        }
        j = 0;
 		i++;
    		//expand_var();
		
 	}
}