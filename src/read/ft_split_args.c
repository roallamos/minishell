/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:18:15 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/11 20:06:54 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	only_spaces(const char *command)
{
	int	i;

	i = 0;
	while (ft_isspace(command[i]))
	{
		i++;
		if (!command[i])
			return (1);
	}
	return (0);
}

static char	**trim_spaces(char **args)
{
	int		i;
	char	**ret;

	i = 0;
	ret = NULL;
	if (args)
	{
		while (args[i])
			i++;
		ret = ft_calloc(i + 1, sizeof(char *));
		i = 0;
		while (args[i])
		{
			ret[i] = ft_strtrim(args[i], " \t \n \f \r \v");
			i++;
		}
		ft_free_array(args);
	}
	return (ret);
}

static void	move_quotes(char **args, int i, int *j, char quotes)
{
	if (!quotes || quotes == args[i][*j])
	{
		ft_memmove(&args[i][*j], &args[i][*j + 1],
			ft_strlen(&args[i][*j]));
		if (args[i][*j])
			(*j)--;
	}
}

void	remove_quotes(char **args, int f)
{
	int		i;
	int		j;
	char	quotes;

	quotes = 0;
	i = -1;
	while (args && args[++i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '"' || args[i][j] == '\'')
			{
				if (!quotes)
					quotes = args[i][j];
				else if (quotes == args[i][j])
					quotes = 0;
				move_quotes(args, i, &j, quotes);
			}
			if ((j >= 0 && args[i][j]) || j == -1)
				j++;
		}
		if (f)
			break ;
	}
}

char	**ft_split_args(char *command, t_data *data)
{
	char	**ret;
	int		nb;

	data->d_quote = 0;
	data->s_quote = 0;
	nb = args_nb(command, data);
	if (!nb)
		return (NULL);
	ret = ft_calloc(nb + 1, sizeof(char *));
	data->s_quote = 0;
	data->d_quote = 0;
	ft_cut_cmd(command, ret, data);
	ret = trim_spaces(ret);
	return (ret);
}
