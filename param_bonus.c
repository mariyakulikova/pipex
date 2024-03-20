/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:09:25 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/20 16:26:05 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// TODO
void	free_param(t_param *params)
{
	// int	i;

	// free_split(params->cmds_path);
	// i = 0;
	// while (*(params->cmds + i))
	// {
	// 	free_split(*(params->cmds + i));
	// 	i++;
	// }
	// free(params->cmds);
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
	return (param);
}

static int	**pipes_init(t_param *param, int size)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(sizeof(int *) * size + 1);
	if (!pipes)
		exit (EXIT_FAILURE);
	*(pipes + size + 1) = NULL;
	i = 0;
	while (i < size + 1)
	{
		*(pipes + i) = (int *)malloc(sizeof(int) * 2);
		if (!(*(pipes + i)))
			exit(EXIT_FAILURE);
		if (pipe(pipes[i]) == -1)
			my_exit(param, "Pipe error", EXIT_FAILURE);
		i++;
		// printf("end[0] - %d, end[1] - %d\n", pipes[i][0], pipes[i][1]);
	}
	return (pipes);
}

void	set_param(t_param *param, int argc, char **argv, char **envp)
{
	int	size;
	int	i;

	size = argc - 3;
	param->pids = (pid_t *)malloc(sizeof(pid_t) * size);
	if (!param->pids)
		exit (EXIT_FAILURE);
	param->proccesses_count = size;
	param->envp = envp;
	set_path_value(param, envp);
	param->cmds_path = ft_split(param->path, ':');
	parse_cmds(param, argc, argv);
	param->pipes = pipes_init(param, size + 1);
	open_files(*(argv + 1), *(argv + argc - 1), param);
}
