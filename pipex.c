/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:11:09 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/18 18:17:40 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	my_execve(t_param *params, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(params->cmds_path, cmd[0]);
	if (cmd_path == NULL)
		my_exit(params, cmd[0], EXIT_FAILURE);
	if (execve(cmd_path, cmd, params->envp) == -1)
		my_exit(params, "execve error", EXIT_FAILURE);
}

static void	child(t_param *params, int end[2])
{
	if (dup2(params->infile_fd, 0) == -1 || dup2(end[1], 1) == -1)
		my_exit(params, "dup2 error", EXIT_FAILURE);
	close(end[0]);
	close(params->infile_fd);
	my_execve(params, params->cmds[0]);
}

static void	parent(t_param *params, int end[2])
{
	if (dup2(params->outfile_fd, 1) == -1 || dup2(end[0], 0) == -1)
		my_exit(params, "dup2 error", EXIT_FAILURE);
	close(end[1]);
	close(params->outfile_fd);
	my_execve(params, params->cmds[1]);
}

void	pipex(t_param *params)
{
	int	end[2];
	int	status;

	if (pipe(end) == -1)
		my_exit(params, "pipe error", EXIT_FAILURE);
	params->pid = fork();
	if (params->pid == -1)
		my_exit(params, "fork error", EXIT_FAILURE);
	if (params->pid == 0)
		child(params, end);
	parent(params, end);
	waitpid(params->pid, NULL, 0);
}
