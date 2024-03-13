/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:15:04 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/13 19:20:12 by mkulikov         ###   ########.fr       */
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
	char	***cmds;
	pid_t	pid_1;
	pid_t	pid_2;
	int		infile_fd;
	int		outfile_fd;
}			t_param;

void	parse_params(t_param *params, int argc, char **argv, char **envp);
void	free_param(t_param *params);
void	free_split(char **split);
void	test(t_param *params);
void	pipex(t_param *params);
void	child(t_param *params, int pipe_fd[2]);

#endif
