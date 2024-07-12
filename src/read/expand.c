#include <minishell.h>

void	expand_var(t_data *data, int pos)
{
	char	*temp;

	temp = data->list->args[pos];
	data->list->args[pos] = getenv(&data->commands[pos][1]);
	free(temp);
}

 char	**expansor(t_data *data)
 {
 	int i;
    int j;
	char	quote;

 	i = 0;
    j = 0;
	quote = 0;
 	/*while (data->list->args && data->list->args[i])
 	{
		if (data->list->args[i][j] == '\'' || data->list->args[i][j] == '"')
		{
			if (!quote)
				quote = data->list->args[i][j];
			else if (quote == data->list->args[i][j])
				quote = 0;
		}
		else if (data->list->args[i][j] == '$' && quote != '\'')
			expand_var

 	}*/
}