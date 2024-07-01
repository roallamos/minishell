/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/07/01 13:06:41 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	nb_pipes(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(tokens[i])
	{
		if (*tokens[i] == '|')
			j++;
		i++;
	}
	return (j);
}

char	**ft_join_cmd(char **tokens)
{
	int	i;
	int	j;
	char	**ret;
	
	i = 0;
	j = 0;
	ret = ft_calloc(nb_pipes(tokens) + 2, sizeof(char *));
	if (!ret)
		return (NULL);
	while (tokens[i])
	{
		ret[j] = ft_strjoin(tokens[i], " ");
		i++;
		while (tokens[i] && *tokens[i] != '|')
		{
			ret[j] = ft_strjoin_free(ret[j], tokens[i]);
			ret[j] = ft_strjoin_free(ret[j], " ");
			i++;
		}
		if (tokens[i] && *tokens[i] == '|')
			i++;
		j++;
	}
	return (ret);
}

void	read_input(t_data *data)
{
	while (1)
	{
		set_prompt(data);
		data->input = readline(data->prompt);
		if (!data->input)
			do_exit(data);
		if (*data->input)
			add_history(data->input);
		if (check_input(data->input))
		{
			printf("syntax error near unexpected token\n");
			return ;
		}
		data->tokens = ft_split_input(data->input, data);// liberar despues y preguntar a migumore por la memoria que se reserva ahi en data->commands
		data->commands = ft_join_cmd(data->tokens);
		data->list = ft_prepare_list(data);
		parse(data);
		data->pids = fork();
		if (data->pids == 0)
		get_cmd_and_execute(data);
		else
			waitpid(data->pids, &data->status, 0);
		ft_free_args(data);
		free(data->input);
	}
}
