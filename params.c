/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:29:57 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/12 13:02:05 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_param(t_param *params)
{
	free(params->path);
	free_split(params->path_splited);
	// free(params->path_splited);
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
	return (ft_substr(path, 5, ft_strlen(path)));
}

static void	open_files(char *infile, char *outfile, t_param *params)
{
	params->infile_fd = open(infile, O_RDONLY);
	if (params->infile_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	params->outfile_fd = open(infile, O_CREAT, O_RDONLY, O_TRUNC, 777);
	if (params->outfile_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
}

void	preset_params(t_param *params, char **argv, char **envp)
{
	params->path = get_path_value(envp);
	if (params->path == NULL)
		exit(EXIT_FAILURE);
	params->path_splited = ft_split(params->path, ':');
	open_files(*(argv + 1), *(argv + 4), params);
}
