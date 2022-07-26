/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:14:48 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/21 17:14:50 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//create a new process for each command

/*
have an int that tracks the number of pipes that are present

go over the command linked list
while (list)
{
	//there is a check here i dont understand, if data->cmd[0] == 0
	run the pipe
		(it is a good idea to give to each command node the result of the pid, because i will need it later, so save it in the structure) 
	list = list->next // go to the next node;
}
if there is one or more pipes left 
	close(pipe[0]) close the read end of the pipe 
loop over the list again 
while (list)
{
	waitpid(id of current node, )
	list = list->next;
}
*/