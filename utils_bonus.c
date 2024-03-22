/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:22:33 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/22 18:21:26 by mkulikov         ###   ########.fr       */
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
