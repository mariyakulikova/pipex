/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:52 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/20 16:30:53 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	waitpids(t_param *param, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		waitpid(param->pids[i], NULL, 0);
		i++;
	}
}

static void	my_execve(t_param *param, char **cmd)
{
	char	*cmd_path;
	printf("my_execve %s\n", cmd[0]);

	cmd_path = get_cmd_path(param->cmds_path, cmd[0]);
	if (cmd_path == NULL)
		my_exit(param, cmd[0], EXIT_FAILURE);
	if (execve(cmd_path, cmd, param->envp) == -1)
		my_exit(param, "execve error", EXIT_FAILURE);
}

static void	child(t_param *param, int *end, int i)
{
	printf("%s", "YA TUT \n");
	if (i == 0)
	{
		close(end[0]);
		if (dup2(param->infile_fd, 0) == -1 || dup2(end[1], 1) == -1)
			my_exit(param, "dup2 error", EXIT_FAILURE);
	}
	else if (i == param->proccesses_count - 2)
	{
		close(end[1]);
		if (dup2(param->outfile_fd, 1) == -1 || dup2(end[0], 0) == -1)
			my_exit(param, "dup2 error", EXIT_FAILURE);
	}
	else
	{
		if (dup2(end[1], 1) == -1 || dup2(end[0], 0) == -1)
			my_exit(param, "dup2 error", EXIT_FAILURE);
	}
	close_files(param, i);
	my_execve(param, param->cmds[i]);
}

void	pipex(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->proccesses_count)
	{
		param->pids[i] = fork();
		if (param->pids[i] == 0)
		{
			child(param, param->pipes[i], i);
			break ;
		}
		i++;
	}
	close_files(param, -1);
}
