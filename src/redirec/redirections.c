/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:18:42 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/28 22:18:44 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redir_start(char **args)
{
	int	i;

	if (args[0] == NULL)
		return (-1);
	if (args[1])
	{
		if ((ft_strcmp(args[0], ">") == 0) && (ft_strcmp(args[1], ">")))
			return (1);
		if ()
	}
	
	
}

int	set_redir(t_list *cmds)
{
	t_list *curr;

	if (cmds == NULL)
		return (-1);
	else
	{
		curr = cmds;
		while (curr != NULL)
		{

		}
	}
}