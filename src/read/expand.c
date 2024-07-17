#include <minishell.h>

char	*ft_replace(char *var, char *value, char *args)
{
	int	i;
	char	*ret;

	i = 0;
	while (args[i] && args[i] != '$')
		i++;
	if (args[i])
	{
		ret = ft_strndup(args, i);
		ret = ft_strjoin_free(ret, value);
		i += ft_strlen(var);
		ret = ft_strjoin_free(ret, &args[i]);
	}
	free(args);
	return (ret);
}

char *get_from_env(t_data *data, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i] && ft_strncmp(data->env[i], &var[1], ft_strlen(&var[1])))
		i++;
	while (data->env[i] && data->env[i][j] != '=')
		j++;
	if (data->env[i][j] == '=')
		j++;
	return (&data->env[i][j]);
}

char	*expand_var(t_data *data, char *args)
{
	int	i;
	int	j;
	char *var;

	i = 0;
	j = 0;
	while (args[i] != '$')
		i++;
	while (args[i + j] && (!ft_isspace(args[i + j]) || args[i + j] == '$'))
		j++;
	var = ft_strndup(&args[i], i - j + 1);
	args = ft_replace(var, get_from_env(data, var), args);
	return (args);
}

 void	expansor(char **args, t_data *data)
 {
 	int i;
    int j;
	char	quote;

 	i = 0;
    j = 0;
	quote = 0;
 	while (args && args[i])
 	{
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '"')
			{
				if (!quote)
					quote = args[i][j];
				else if (quote == args[i][j])
					quote = 0;
			}
			else if (args[i][j] == '$' && quote != '\'')
			{
				args[i] = expand_var(data, args[i]);//expand_var(data, args[i], i); esto va a ser la funcion de sustituir y plantea que igual hay que resetear j 
				printf("%s\n",args[i]);
			}
			if (args[i][j])
				j++;
		}
		j = 0;
		i++;
 	}
}