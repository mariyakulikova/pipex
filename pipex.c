/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:11:09 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/13 19:26:59 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_param *params)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	params->pid_1 = fork();
	if (params->pid_1 < 0)
	{
		perror("Fork");
		exit(EXIT_FAILURE);
	}
	if (params->pid_1 == 0)
	{
		printf("TUT\n");
		child(params, pipe_fd);
	}

}
