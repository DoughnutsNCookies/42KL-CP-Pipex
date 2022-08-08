/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:17:41 by schuah            #+#    #+#             */
/*   Updated: 2022/07/23 14:18:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/srcs/libft.h"
# include "../libft/srcs/ft_printf.h"
# include "../libft/srcs/get_next_line.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_pinfo
{
	int		fd_in;
	int		fd_out;
	int		hd;
	int		ncmd;
	int		npipe;
	int		*pipe;
	int		i;
	char	*cmd_lst;
	char	**cmdpath;
	char	**cmd;
}	t_pinfo;

int		print_error(char *str);
void	pipe_fail(t_pinfo *pinfo);
void	free_parent(t_pinfo *pinfo);
void	free_child(t_pinfo *pinfo);
void	close_pipes(t_pinfo *pinfo);

void	default_pipex_flag(t_pinfo *pinfo);
void	setfd_in(int ac, char **av, t_pinfo *pinfo);
void	setfd_out(int ac, char **av, t_pinfo *pinfo);
void	write_heredoc(int ac, char **av, int fd);
void	here_doc(int ac, char **av, t_pinfo *pinfo);

int		check_hd(int ac, char **av, t_pinfo *pinfo);
void	create_pipes(t_pinfo *pinfo);
void	do_pipe(int ac, char **av, char **evp, t_pinfo *pinfo);

void	dup_redirecting(t_pinfo *pinfo);
char	*comb_cmd(char **lastcmd, char *newcmd, t_pinfo *pinfo);
void	produce(t_pinfo *pinfo, char **av, char **evp);

#endif