/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:11:09 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/16 17:04:16 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	my_execve(t_param *params, char **cmd)
// {
// 	char	*cmd_path[] = "/usr/bin/";
// }

void	child(t_param *params, int *end)
{
	write(1, "child started execve\n", 22);
	if (dup2(params->infile_fd, 0) == -1 || dup2(end[1], 1) == -1)
		my_exit(params, "dup2 error", EXIT_FAILURE);
	close(end[0]);
	close(params->infile_fd);
	char *argv[2] = {"cat", NULL};
	execve("/usr/bin/cat", argv, NULL);
	// my_execve(params, params->cmds[0]);
}

void	parent(t_param *params, int end[2])
{
	printf("%d\n", params->outfile_fd);
	if (dup2(params->outfile_fd, 1) == -1 || dup2(end[0], 0) == -1)
		my_exit(params, "dup2 error", EXIT_FAILURE);
	close(end[1]);
	close(params->outfile_fd);
	char *argv[2] = {"cat", NULL};
	// printf("parent started execve\n");
	execve("/usr/bin/cat", argv, NULL);
	// my_execve(params, params->cmds[1]);
}

void	pipex(t_param *params)
{
	int	end[2];

	if (pipe(end) == -1)
		my_exit(params, "pipe error", EXIT_FAILURE);
	printf("end 0 - %d, end 1 - %d\n", end[0], end[1]);
	params->pid = fork();
	if (params->pid == -1)
		my_exit(params, "fork error", EXIT_FAILURE);
	if (params->pid == 0)
		child(params, end);
	parent(params, end);
}
