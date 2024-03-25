/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:22:33 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/25 14:51:26 by mkulikov         ###   ########.fr       */
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
	write(2, "pipex: ", 8);
	perror(str);
	free_param(params);
	exit(status);
}

void	open_files(char *infile, char *outfile, t_param *params)
{
	if (params->here_doc)
	{
		params->infile_fd = here_doc(params);
		params->outfile_fd = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (params->outfile_fd == -1)
			my_exit(params, outfile, EXIT_FAILURE);
	}
	else
	{
		params->infile_fd = open(infile, O_RDONLY);
		if (params->infile_fd == -1)
			my_exit(params, infile, EXIT_FAILURE);
		params->outfile_fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (params->outfile_fd == -1)
			my_exit(params, outfile, EXIT_FAILURE);
	}
}

void	close_files(t_param *param)
{
	close(param->infile_fd);
	close(param->outfile_fd);
	if (param->here_doc)
		unlink(TMP_FILE);
}

void	err_msg(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(2, str, len);
}
