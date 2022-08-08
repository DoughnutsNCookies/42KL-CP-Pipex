/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_produce_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:41:26 by schuah            #+#    #+#             */
/*   Updated: 2022/07/20 12:28:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Duping to redirect output to respective files */
void	dup_redirecting(t_pinfo *pinfo)
{
	if (pinfo->i == 0)
	{
		dup2(pinfo->fd_in, STDIN_FILENO);
		dup2(pinfo->pipe[1], STDOUT_FILENO);
	}
	else if (pinfo->i == pinfo->ncmd - 1)
	{
		dup2(pinfo->pipe[2 * pinfo->i - 2], STDIN_FILENO);
		dup2(pinfo->fd_out, STDOUT_FILENO);
	}
	else
	{
		dup2(pinfo->pipe[2 * pinfo->i - 2], STDIN_FILENO);
		dup2(pinfo->pipe[2 * pinfo->i + 1], STDOUT_FILENO);
	}
}

/* Combines all commands into a single string,
 * checks whether access is granted to each command */
char	*comb_cmd(char **lastcmd, char *newcmd, t_pinfo *pinfo)
{
	char	*cmd;

	if (access(newcmd, F_OK) == 0)
		return (newcmd);
	while (*lastcmd != NULL)
	{
		cmd = ft_strjoin(ft_strjoin(*lastcmd, "/"), newcmd);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		lastcmd++;
	}
	write(2, "Command not found: ", 19);
	write(2, newcmd, ft_strlen(newcmd));
	write(2, "\n", 1);
	free_child(pinfo);
	exit(128);
}

/* Creates child by forking */
void	produce(t_pinfo *pinfo, char **av, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_redirecting(pinfo);
		close_pipes(pinfo);
		pinfo->cmd = ft_split(av[2 + pinfo->i + pinfo->hd], ' ');
		pinfo->cmd_lst = comb_cmd(pinfo->cmdpath, pinfo->cmd[0], pinfo);
		execve(pinfo->cmd_lst, pinfo->cmd, envp);
	}
}
