/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 22:49:07 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 22:50:45 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_print(char *cmd)
{
	ft_putstr_fd("unset: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": invalid parameter name\n", 2);
	return (1);
}
