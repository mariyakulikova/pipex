/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:18 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/13 19:32:18 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_param *params, int pipe_fd[2])
{
	// printf("dup_1 - %d, dup_2 - %d\n", dup_1, dup_2);
	if (dup2(params->infile_fd, STDIN_FILENO) < 0 \
				|| dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2 error");
		exit(EXIT_FAILURE);
	}
	printf("CHILD END\n");
}
