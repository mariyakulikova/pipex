/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:29:57 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/13 11:48:46 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_param(t_param *params)
{
	free_split(params->cmd_path);
}

static char	*get_path_value(char **envp)
{
	char	*path;

	if (envp == NULL)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			path = *envp;
		envp++;
	}
	path += 5;
	return (path);
}

static int	open_files(char *infile, char *outfile, t_param *params)
{
	params->infile_fd = open(infile, O_RDONLY);
	if (params->infile_fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	params->outfile_fd = open(infile, O_CREAT, O_RDWR, O_TRUNC, 644);
	if (params->outfile_fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	return (0);
}

int	preset_params(t_param *params, char **argv, char **envp)
{
	params->path = get_path_value(envp);
	if (!params->path)
		return (1);
	params->cmd_path = ft_split(params->path, ':');
	if (!params->cmd_path)
		return (1);
	if (open_files(*(argv + 1), *(argv + 4), params) == 1)
		return (1);
	return (0);
}
