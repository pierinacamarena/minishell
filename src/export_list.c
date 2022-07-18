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
Function that sets up the content of a node, assigns that to a node
of the list and returns it.
*/

t_exp_list *ft_set_expo(char *env)
{
    t_exp_list  *list;

    if (!env)
        {return (NULL);}
	list = malloc(sizeof(t_exp_list));
	if (!list)
		{return (NULL);}
	list->content = ft_strdup(env);
	list->next = NULL;
    return (list);
}

/*
Function that loops accross the list and adds the node aux
at the end of the list.
*/

void    ft_add_expo(t_exp_list **begin, t_exp_list *aux)
{
	t_exp_list *temp;

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
Function that creates a linked list of the environment variables
that will be used for the function export.
*/

t_exp_list	*init_exp(char **env)
{
    t_exp_list  *begin;
    t_exp_list  *aux;
	int			i;

	i = 0;
    begin = NULL;
    while (env[i])
    {
        aux = ft_set_expo(env[i]);
		ft_add_expo(&begin, aux);
		i++;
    }
	return (begin);
}

/*
Function that prints the list
*/
void	ft_print_export(t_exp_list *begin)
{
	t_exp_list *temp;

	if (begin == NULL)
		return ;
	else
	{
		temp = begin;
		while (temp->next)
		{
			printf("%s\n",temp->content);
			temp = temp->next;
		}
		printf("%s\n",temp->content);
	}
}
