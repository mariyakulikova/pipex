/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:15:04 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/18 18:00:59 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_param {
	char	*path;
	char	**cmds_path;
	char	***cmds;
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	char	**envp;
}			t_param;

void	free_param(t_param *params);
void	free_split(char **split);
void	test(t_param *params);
void	pipex(t_param *params);
void	my_exit(t_param *params, char *str, int status);
void	set_path_value(t_param *params, char **envp);
void	open_files(char *infile, char *outfile, t_param *params);
void	parse_cmds(t_param *params, int argc, char **argv);
char	*get_cmd_path(char **cmds_path, char *cmd);

#endif
