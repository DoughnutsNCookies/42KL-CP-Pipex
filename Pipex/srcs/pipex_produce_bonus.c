/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_produce_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:41:26 by schuah            #+#    #+#             */
/*   Updated: 2022/09/09 15:23:00 by schuah           ###   ########.fr       */
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
	char	*temp;

	if (access(newcmd, F_OK) == 0)
		return (newcmd);
	while (*lastcmd != NULL)
	{
		temp = ft_strjoin(*lastcmd, "/");
		cmd = ft_strjoin(temp, newcmd);
		if (access(cmd, F_OK) == 0)
		{
			free(temp);
			return (cmd);
		}
		free(cmd);
		free(temp);
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
