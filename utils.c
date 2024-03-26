/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:37:23 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/26 15:24:53 by mkulikov         ###   ########.fr       */
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

static void	err_msg(char *s1, char *s2)
{
	write(2, s1, ft_strlen(s1));
	write(2, ": ", 2);
	write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
}

void	my_exit(t_param *params, char *err, char *name)
{
	char	*strerr;

	strerr = strerror(errno);
	write(2, "pipex: ", 8);
	if (ft_strcmp(err, ERR_CMD) == 0)
		err_msg(err, name);
	else if (ft_strcmp(err, ERR_OPEN) == 0)
		err_msg(strerr, name);
	else
		perror(err);
	free_param(params);
	exit(EXIT_FAILURE);
}

void	open_files(char *infile, char *outfile, t_param *params)
{
	params->infile_fd = open(infile, O_RDONLY);
	if (params->infile_fd == -1)
		my_exit(params, ERR_OPEN, infile);
	params->outfile_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (params->outfile_fd == -1)
		my_exit(params, ERR_OPEN, outfile);
}

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
