/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:45:52 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/07 14:56:05 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	same_value_helper(t_env_list *list, char *info_one, char *info_two)
{
	t_env_list	*curr;

	curr = list;
	while (curr != NULL)
	{
		if (curr->node->key && info_one && \
		ft_strcmp(curr->node->key, info_one) == 0)
		{
			if (curr->node->content && info_two && \
			ft_strcmp(curr->node->content, info_two) == 0)
			{
				free(info_one);
				free(info_two);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}
