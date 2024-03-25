/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:09:25 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/25 11:07:59 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_param(t_param *params)
{
	int	i;


	i = 0;
	if (params->cmds != NULL)
	{
		while (*(params->cmds + i))
		{
			free_split(*(params->cmds + i));
			i++;
		}
		free(params->cmds);
	}
	if (params->cmds_path != NULL)
		free_split(params->cmds_path);
	if (params->pids != NULL)
		free(params->pids);
	if (params->pipes != NULL)
		free(params->pipes);
	free(params);
}

t_param	*param_init(void)
{
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		exit (EXIT_FAILURE);
	param->pids = NULL;
	param->pipes = NULL;
	param->path = NULL;
	param->cmds_path = NULL;
	param->cmds = NULL;
	param->envp = NULL;
	param->here_doc = 0;
	param->limiter = NULL;
	return (param);
}

static int	*pipes_init(t_param *param, int size)
{
	int	*pipes;
	int	i;

	pipes = (int *)malloc(sizeof(int) * size);
	if (!pipes)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		if (pipe(pipes + i) < 0)
			my_exit(param, ERR_PIPE, EXIT_FAILURE);
		i += 2;
	}
	return (pipes);
}



void	set_param(t_param *param, int argc, char **argv, char **envp)
{
	int	size;
	int	i;

	if (param->here_doc)
		param->limiter = argv[2];
	size = argc - param->here_doc - 3;
	param->cmd_num = size;
	param->pipes_size = (size - 1) * 2;
	open_files(*(argv + 1), *(argv + argc - 1), param);
	param->pids = (pid_t *)malloc(sizeof(pid_t) * size);
	if (!param->pids)
		exit (EXIT_FAILURE);
	param->envp = envp;
	set_path_value(param, envp);
	param->cmds_path = ft_split(param->path, ':');
	parse_cmds(param, argc, argv);
	param->pipes = pipes_init(param, param->pipes_size);
}
