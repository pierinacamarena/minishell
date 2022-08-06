/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:43:52 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 20:26:50 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Function that loops accross the list and adds the node aux
at the end of the list.
*/

void	ft_add_node(t_env_list **begin, t_env_list *aux)
{
	t_env_list	*temp;

	if (*begin == NULL)
		*begin = aux;
	else
	{
		temp = *begin;
		while (temp->next)
			temp = temp->next;
		temp->next = aux;
	}
}

/*
Free a linked list
*/

void	ft_free_list(t_env_list **begin)
{
	t_env_list	*curr;
	t_env_list	*aux;

	if (*begin == NULL)
		return ;
	else
	{
		curr = *begin;
		while (curr != NULL)
		{
			aux = curr;
			curr = curr->next;
			free(aux->node->key);
			free(aux->node->content);
			free(aux->node);
			free(aux);
		}
		*begin = NULL;
	}
}

/*
Function that creates a linked list and allocates to each node
two char * values. The first value is key has the content before 
and including the "=". The second value is content, these values
are stored in a struct
*/

t_env_list	*init_env(char **env)
{
	t_env_list	*begin;
	t_env_list	*aux;
	int			i;

	i = 0;
	begin = NULL;
	while (env[i])
	{
		aux = ft_set_node(env[i]);
		ft_add_node(&begin, aux);
		i++;
	}
	return (begin);
}

/*
Function that prints the list
*/
void	ft_print_list(t_env_list *begin)
{
	t_env_list	*temp;

	if (begin == NULL)
		return ;
	else
	{
		temp = begin;
		while (temp != NULL)
		{
			if (temp->node->content != NULL)
				printf("%s%s\n", temp->node->key, temp->node->content);
			else
				printf("%s\n", temp->node->key);
			temp = temp->next;
		}
	}
}
