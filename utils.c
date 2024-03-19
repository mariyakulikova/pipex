/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:37:23 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/19 17:19:49 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (*(split + i))
	{
		free(*(split + i));
		i++;
	}
	free(split);
}

void	my_exit(t_param *params, char *str, int status)
{
	perror(str);
	free_param(params);
	exit(status);
}

void	open_files(char *infile, char *outfile, t_param *params)
{
	params->infile_fd = open(infile, O_RDONLY);
	if (params->infile_fd == -1)
		my_exit(params, "Error opening infile", EXIT_FAILURE);
	params->outfile_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (params->outfile_fd == -1)
		my_exit(params, "Error opening outfile", EXIT_FAILURE);
}

// void	close_files(int fd1, int fd2)
// {
// 	close(fd1);
// 	close(fd2);
// }

void	free_param(t_param *params)
{
	int	i;

	free_split(params->cmds_path);
	i = 0;
	while (*(params->cmds + i))
	{
		free_split(*(params->cmds + i));
		i++;
	}
	free(params->cmds);
}
