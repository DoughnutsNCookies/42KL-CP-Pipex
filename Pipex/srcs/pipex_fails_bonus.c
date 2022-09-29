/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fails_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:10:57 by schuah            #+#    #+#             */
/*   Updated: 2022/09/29 20:48:59 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Prints custom error message */
int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

/* Closes fd, free pipe and output error message */
void	pipe_fail(t_pinfo *pinfo)
{
	if (pinfo->hd == 1)
		unlink(".hd_temp");
	close(pinfo->fd_in);
	close(pinfo->fd_out);
	free(pinfo->pipe);
	perror("Environment");
	exit(1);
}

/* Free the parent */
void	free_parent(t_pinfo *pinfo)
{
	int	i;

	if (pinfo->hd == 1)
		unlink(".hd_temp");
	close(pinfo->fd_in);
	close(pinfo->fd_out);
	free(pinfo->pipe);
	i = -1;
	while (pinfo->cmdpath[++i] != NULL)
		free(pinfo->cmdpath[i]);
}

/* Free the child */
void	free_child(t_pinfo *pinfo)
{
	int	i;

	i = -1;
	while (pinfo->cmdpath[++i] != NULL)
		free(pinfo->cmdpath[i]);
	free(pinfo->cmd_lst);
	free(pinfo->cmd);
}

/* Closes the pipes */
void	close_pipes(t_pinfo *pinfo)
{
	int	i;

	i = -1;
	while (pinfo->npipe > ++i)
		close(pinfo->pipe[i]);
}
