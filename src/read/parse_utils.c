#include "minishell.h"

void	set_quotes(char c, int *d_quote, int *s_quote)
{
	if (c == '\'' && !*s_quote && !*d_quote)
		*s_quote = 1;
	else if (c == '\'' && *s_quote)
		*s_quote = 0;
	if (c == '"' && !*d_quote && !*s_quote)
		*d_quote = 1;
	else if (c == '"' && *d_quote)
		*d_quote = 0;
}