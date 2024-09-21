/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:24:58 by migumore          #+#    #+#             */
/*   Updated: 2024/09/21 17:16:44 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//  void	print_list(t_cmd *list)
//  {
//  	int	i;

//  	while (list)
//  	{
//  		printf("%s\n", list->cmd);
//  		i = 0;
//  		while (list->args[i])
//  		{
//  			printf("args %s\n", list->args[i]);
//  			i++;
//  		}
// 		i = 0;
// 		while (list->docs && list->docs[i].doc)
// 		{
// 			printf("doc: %s flag: %i\n", list->docs[i].doc, list->docs[i].flag);
// 			i++;
// 		}
//  		/*i = 0;
//  		while (list->outfile && list->outfile[i])
//  		{
//  			printf("outfile %s\n", list->outfile[i]);
//  			i++;
//  		}
//  		i = 0;
//  		while (list->infile && list->infile[i])
//  		{
//  			printf("infile %s\n", list->infile[i]);
//  			i++;
//  		}
//  		i = 0;
//  		while (list->heredoc && list->heredoc[i])
//  		{
//  			printf("heredoc %s\n", list->heredoc[i]);
//  			i++;
//  		}
//  		i = 0;
//  		while (list->append && list->append[i])
//  		{
//  			printf("append %s\n", list->append[i]);
//  			i++;makmam
//  		}*/
//  		list = list->next;
//  	}
// }

void	read_input(t_data *data)
{
	while (1)
	{
		set_prompt(data);
		data->input = readline(data->prompt);
		add_history(data->input);
		if (!data->input)
		{
			ft_free_lst(data);
			printf("exit\n");
			exit(0);
		}
		else if (check_input(data->input))
			printf("syntax error near unexpected token\n");
		else
		{
			data->commands = ft_split_input(data->input);
			if (data->commands && ft_strcmp(data->commands[0], "\0"))
			{
				data->list = ft_prepare_list(data);
				//print_list(data->list);
				if (data->list->args)
					execute(data);
			}
			else
				ft_free_array(data->commands);
		}
		ft_free_lst(data);
	}
}
