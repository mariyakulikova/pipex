/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:15:04 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/26 15:16:41 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

# define ERR_ARGS "Invalid number of arguments\n"
# define ERR_PIPE "Pipe error"
# define ERR_DUP2 "Dup2 error"
# define ERR_FORK "Fork error"
# define ERR_EXEC "Execve error"
# define ERR_OPEN "File opening error"
# define ERR_READ "Reading error"
# define ERR_CMD "command not found"
# define ERR_SPLT "Split error"
# define ERR_ENVP "envp is NULL"

typedef struct s_param {
	pid_t	pid1;
	pid_t	pid2;
	char	*path;
	char	**cmds_path;
	char	***cmds;
	char	**envp;
	int		infile_fd;
	int		outfile_fd;

}			t_param;

void	free_param(t_param *params);
void	free_split(char **split);
void	pipex(t_param *params);
void	my_exit(t_param *params, char *err, char *name);
void	set_path_value(t_param *params, char **envp);
void	open_files(char *infile, char *outfile, t_param *params);
void	parse_cmds(t_param *params, int argc, char **argv);
char	*get_cmd_path(char **cmds_path, char *cmd);

#endif
