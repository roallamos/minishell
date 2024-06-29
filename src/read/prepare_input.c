
#include <minishell.h>

int	nb_tokens(char **args, char *c)
{
	int	i;
	int	nb;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], c))
			nb++;
		i++;
	}
	return (nb);
}

char	**ft_redir(char **args, char *token)
{
	int	i;
	int	nb;
	char	**redir;
	
	i = 0;
	nb = nb_tokens(args, token);
	if (nb == 0)
		return (NULL);
	redir = ft_calloc(nb + 1, sizeof(char *));
	while (args[i])
	{
		if (!ft_strcmp(args[i], token))
			redir[i] = ft_strdup(args[i + 1], 0, ft_strlen(args[i + 1]));
		i++;
	}
	return (redir);
}

t_command_list	*ft_new_node(char *commands)
{
	t_command_list	*list;

	list = ft_calloc(1, sizeof(t_command_list));
	list->commands = ft_substr(commands, 0, ft_strlen(commands));
	list->args = ft_split(commands, ' ');
	list->outfile = ft_redir(list->args, ">");
	list->infile = ft_redir(list->args, "<");
	list->heredock = ft_redir(list->args, "<<");
	list->migu_dale_nombre = ft_redir(list->args, ">>");
	list->next = NULL;
	return (list);
}

t_command_list	*ft_prepare_list(t_data *data)
{
	t_command_list	*list;
	int	i;

	i = 0;
	while (data->commands[i])
	{
		list = ft_lstadd_back(&list, ft_new_node(data->commands[i]));
		i++;
	}
	return (list);
}
