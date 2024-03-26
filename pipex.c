/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:11:09 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/26 14:52:52 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	my_execve(t_param *params, char **cmd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(params->cmds_path, cmd[0]);
	if (cmd_path == NULL)
		my_exit(params, ERR_CMD, cmd[0]);
	if (execve(cmd_path, cmd, params->envp) == -1)
		my_exit(params, ERR_EXEC, NULL);
}

static void	child1(t_param *params, int end[2])
{
	if (dup2(params->infile_fd, 0) == -1 || dup2(end[1], 1) == -1)
		my_exit(params, ERR_DUP2, NULL);
	close(end[0]);
	close(params->infile_fd);
	close(params->outfile_fd);
	my_execve(params, params->cmds[0]);
}

static void	child2(t_param *params, int end[2])
{
	if (dup2(params->outfile_fd, 1) == -1 || dup2(end[0], 0) == -1)
		my_exit(params, ERR_DUP2, NULL);
	close(end[1]);
	close(params->infile_fd);
	close(params->outfile_fd);
	my_execve(params, params->cmds[1]);
}

void	pipex(t_param *params)
{
	int	end[2];

	if (pipe(end) == -1)
		my_exit(params, ERR_PIPE, NULL);
	params->pid1 = fork();
	if (params->pid1 == -1)
		my_exit(params, ERR_FORK, NULL);
	if (params->pid1 == 0)
		child1(params, end);
	params->pid2 = fork();
	if (params->pid2 == -1)
		my_exit(params, ERR_FORK, NULL);
	if (params->pid2 == 0)
		child2(params, end);
	close(end[0]);
	close(end[1]);
}
