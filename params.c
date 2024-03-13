/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:29:57 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/13 14:10:19 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_param(t_param *params)
{
	free_split(params->cmd_path);
}

static void	*set_path_value(t_param *params, char **envp)
{
	if (envp == NULL)
	{
		perror("envp is NULL");
		exit(EXIT_FAILURE);
	}
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			params->path = *envp;
			break ;
		}
		envp++;
	}
	// params->path = NULL;
}

static void	open_files(char *infile, char *outfile, t_param *params)
{
	params->infile_fd = open(infile, O_RDONLY);
	if (params->infile_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	params->outfile_fd = open(infile, O_CREAT, O_RDWR, O_TRUNC, 0644);
	if (params->outfile_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
}

void	init_params(t_param *params, char **argv, char **envp)
{
	set_path_value(params, envp);
	params->cmd_path = ft_split(params->path, ':');
	open_files(*(argv + 1), *(argv + 4), params);
}
