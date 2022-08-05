/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:20:31 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/05 13:20:41 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Function that takes the list with the content of env back to a char ** to be
used for the execve function
*/

char	**list_to_array(t_env_list *list)
{
	char		**env_exec;
	t_env_list	*curr;
	int			i;

	i = 0;
	if (list == NULL)
		return (NULL);
	env_exec = (char **)malloc(sizeof(char *) * (list_size(list) + 1));
	if (!env_exec)
		return (NULL);
	curr = list;
	while (curr != NULL)
	{
		env_exec[i] = ft_strjoin(curr->node->key, curr->node->content);
		curr = curr->next;
		i++;
	}
	env_exec[i] = NULL;
	return (env_exec);
}

/*
Prints the env char **
*/

void	print_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
