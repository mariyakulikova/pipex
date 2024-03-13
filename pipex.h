/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:15:04 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/13 11:48:23 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_param {
	char	*path;
	char	**cmd_path;
	pid_t	pid_1;
	pid_t	pid_2;
	int		infile_fd;
	int		outfile_fd;
}			t_param;

int	preset_params(t_param *params, char **argv, char **envp);
void	free_param(t_param *params);
void	free_split(char **split);
void	test(t_param *params);
void	pipex(t_param *params);

#endif
