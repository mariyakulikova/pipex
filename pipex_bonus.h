/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:31:50 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/20 16:30:38 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_param {
	pid_t	*pids;
	int		**pipes;
	char	*path;
	char	**cmds_path;
	char	***cmds;
	char	**envp;
	int		infile_fd;
	int		outfile_fd;
	int		proccesses_count;
}			t_param;

t_param	*param_init(void);
void	set_param(t_param *param, int argc, char **argv, char **envp);
void	free_param(t_param *params);
void	free_split(char **split);
void	my_exit(t_param *params, char *str, int status);
void	open_files(char *infile, char *outfile, t_param *params);
void	parse_cmds(t_param *params, int argc, char **argv);
void	set_path_value(t_param *params, char **envp);
char	*get_cmd_path(char **cmds_path, char *cmd);
void	pipex(t_param *param);
void	waitpids(t_param *param, int size);
void	close_files(t_param *param, int j);

#endif
