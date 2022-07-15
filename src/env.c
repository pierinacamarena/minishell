/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:43:52 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/11 16:43:55 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Function that splits the content of the current array inside
char **env. It splits it at the "=" and assigns that to a node
of the list and returns it.
*/

t_env_list *ft_set_node(char *env)
{
    char        **info;
	char		*temp;
    t_env_list  *list;
	t_env		*node_env;

    if (!env)
        return (NULL);
    info = ft_split(env, '=');
	temp = ft_strjoin(info[0], "=");
	free(info[0]);
	info[0] = temp;
	list = malloc(sizeof(t_env_list));
	if (!list)
		return (NULL);
	node_env = malloc(sizeof(t_env));
	if (!node_env)
		return (NULL);
	list->node = node_env;
    list->node->key = info[0];
    list->node->content = info[1];
	list->next = NULL;
    return (list);
}

/*
Function that loops accross the list and adds the node aux
at the end of the list.
*/

void    ft_add_node(t_env_list **begin, t_env_list *aux)
{
	t_env_list *temp;

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
Function that creates a linked list and allocates to each node
two char * values. The first value is key has the content before 
and including the "=". The second value is content, these values
are stored in a struct
*/

t_env_list	*init_env(char **env)
{
    int i;
    t_env_list  *begin;
    t_env_list  *aux;
	t_env_list	*temp;

    begin = NULL;
	i = 0;

    while (env[i])
    {
        aux = ft_set_node(env[i]);
		ft_add_node(&begin, aux);
        i++;
    }
	temp = begin;
	while (temp->next)
	{
		temp->size = i;
		temp = temp->next;
	}
	return (begin);
}

/*
Function that prints the list
*/
void	ft_print_list(t_env_list *begin)
{
	t_env_list *temp;

	if (begin == NULL)
		return ;
	else
	{
		temp = begin;
		while (temp->next)
		{
			printf("%s%s\n", temp->node->key, temp->node->content);
			temp = temp->next;
		}
		printf("%s%s\n", temp->node->key, temp->node->content);
	}
}
