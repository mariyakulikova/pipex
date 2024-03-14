/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:29:57 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/14 15:38:37 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_param(t_param *params)
{
	int	i;

	free_split(params->cmd_path);
	i = 0;
	while (*(params->cmds + i))
	{
		free_split(*(params->cmds + i));
		i++;
	}
	free(params->cmds);
}

static void	set_path_value(t_param *params, char **envp)
{
	if (envp == NULL)
		my_exit(params, "envp is NULL", EXIT_SUCCESS);
	params->path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			params->path = *envp;
			break ;
		}
		envp++;
	}
}

static void	open_files(char *infile, char *outfile, t_param *params)
{
	params->infile_fd = open(infile, O_RDONLY);
	if (params->infile_fd == -1)
		my_exit(params, "Error opening file", EXIT_FAILURE);
	params->outfile_fd = open(infile, O_CREAT, O_RDWR, O_TRUNC, 0644);
	if (params->outfile_fd == -1)
		my_exit(params, "Error opening file", EXIT_FAILURE);
}

static void	parse_cmds(t_param *params, int argc, char **argv)
{
	int	size;
	int	i;

	size = argc - 3;
	params->cmds = (char ***)malloc(sizeof(char **) * (size + 1));
	*(params->cmds + size) = NULL;
	i = 0;
	while (i < size)
	{
		*(params->cmds + i) = ft_split(*(argv + 2 + i), ' ');
		if (*(params->cmds + i) == NULL)
			my_exit(params, "Spliting error", EXIT_FAILURE);
		i++;
	}
}

void	parse_params(t_param *params, int argc, char **argv, char **envp)
{
	set_path_value(params, envp);
	params->cmd_path = ft_split(params->path, ':');
	open_files(*(argv + 1), *(argv + 4), params);
	parse_cmds(params, argc, argv);
}
