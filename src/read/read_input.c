/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/07/09 13:08:49 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	nb_pipes(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (*tokens[i] == '|')
			j++;
		i++;
	}
	return (j);
}

static char	**ft_join_cmd(char **tokens, t_data *data)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	ret = ft_calloc(nb_pipes(tokens) + 2, sizeof(char *));
	if (!ret)
		return (NULL);
	while (tokens[i])
	{
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
	ft_free_array(data->commands);
	return (ret);
}

// void	print_list(t_cmd *list)
// {
// 	int	i;

// 	while (list)
// 	{
// 		printf("%s\n", list->cmd);
// 		i = 0;
// 		while (list->args[i])
// 		{
// 			printf("args %s\n", list->args[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (list->outfile && list->outfile[i])
// 		{
// 			printf("outfile %s\n", list->outfile[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (list->infile && list->infile[i])
// 		{
// 			printf("infile %s\n", list->infile[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (list->heredock && list->heredock[i])
// 		{
// 			printf("heredock %s\n", list->heredock[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (list->append && list->append[i])
// 		{
// 			printf("append %s\n", list->append[i]);
// 			i++;
// 		}
// 		list = list->next;
// 	}
// }

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
			printf("syntax error near unexpected token\n");
		else
		{
			//printf("input %s\n", data->input);
			data->tokens = ft_split_input(data->input, data);
			data->commands = ft_join_cmd(data->tokens, data);
			data->list = ft_prepare_list(data);
			//print_list(data->list);
			parse(data);
		}
		ft_free_lst(data);
		free(data->input);
	}
}
