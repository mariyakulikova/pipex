/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:22:33 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/20 16:30:08 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	close_files(t_param *param, int j)
{
	int	i;

	close(param->infile_fd);
	close(param->outfile_fd);
	i = 0;
	while (*(param->pipes + i))
	{
		if (i != j)
		{
			close(param->pipes[i][0]);
			close(param->pipes[i][1]);
		}
		i++;
	}
}
