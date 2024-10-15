/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:40:00 by rodralva          #+#    #+#             */
/*   Updated: 2024/10/15 21:49:37 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_quotes(char c, int *d_quote, int *s_quote)
{
	if (c == '\'' && !*s_quote && !*d_quote)
		*s_quote = 1;
	else if (c == '\'' && *s_quote)
		*s_quote = 0;
	if (c == '"' && !*d_quote && !*s_quote)
		*d_quote = 1;
	else if (c == '"' && *d_quote)
		*d_quote = 0;
	if (*s_quote || *d_quote)
		return (1);
	else
		return (0);
}
