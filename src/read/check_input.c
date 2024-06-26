/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:42:14 by rodralva          #+#    #+#             */
/*   Updated: 2024/06/26 15:42:20 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_istoken(int a)
{
	if (a != '|' && a != '<' && a != '>')
		return (0);
	return (1);
}
int	nb_redirections(char *input, int *i)
{
	int		j;
	int		k;
	
	j = 0;
	k = 0;
	while (input[*i + k] == '<' || input[*i + k] == '>' || ft_isspace(input[*i + k]))
	{
		if (!ft_isspace(input[*i + k]))
			j++;
		if (j > 2)
			return (1);
		k++;
	}
	return (0);
}

int	check_token(char *input, int *i)
{
	char	last_token;

	if (nb_redirections(input, i))
		return (1);
	last_token = input[*i];
	while(ft_istoken(input[*i]) || ft_isspace(input[*i]))
	{
		*i += 1;
		if (last_token == '|' && (input[*i] == '|' || *i - 1 == 0 || !input[*i]))
			return (1);
		else if (last_token == '<' && input[*i] != '<' && !ft_isspace(input[*i]) && (ft_istoken(input[*i]) || !input[*i]))
			return	(1);
		else if (last_token == '>' && (input[*i] != '>' || input[*i] != '|') && !ft_isspace(input[*i]) && (ft_istoken(input[*i]) || !input[*i]))
			return	(1);
		if (ft_istoken(input[*i]))
			last_token = input[*i];
	}
	return (0);
}

int	check_input(char *input)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isspace(input[j]))
		j++;
	while(input[i + j])
	{
		if (ft_istoken(input[i + j]))
		{
			if (check_token(input + j, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}