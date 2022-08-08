/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:56:42 by schuah            #+#    #+#             */
/*   Updated: 2022/07/23 14:19:40 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Set all variables in struct to default */
void	default_pipex_flag(t_pinfo *pinfo)
{
	pinfo->fd_in = 0;
	pinfo->fd_out = 0;
	pinfo->hd = 0;
	pinfo->ncmd = 0;
	pinfo->npipe = 0;
	pinfo->pipe = NULL;
	pinfo->i = 0;
	pinfo->cmd_lst = NULL;
	pinfo->cmdpath = NULL;
	pinfo->cmd = NULL;
}

/* Set infile file descriptor to pinfo*/
void	setfd_in(int ac, char **av, t_pinfo *pinfo)
{
	if (ft_strncmp("here_doc", av[1], 9) == 0)
		here_doc(ac, &av[2], pinfo);
	else
	{
		pinfo->fd_in = open(av[1], O_RDONLY);
		if (pinfo->fd_in == -1)
		{
			perror("Infile Error");
			exit(1);
		}
	}
}

/* Set outfile file descriptor to pinfo */
void	setfd_out(int ac, char **av, t_pinfo *pinfo)
{
	if (pinfo->hd == 1)
		pinfo->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		pinfo->fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pinfo->fd_out == -1)
		{
			perror("Outfile Error");
			exit(1);
		}
	}
}

/* Writes into a tmp file for here_doc */
void	write_heredoc(int ac, char **av, int fd)
{
	char	*input;
	int		npipe;

	while (1)
	{
		npipe = ac - 4;
		while (--npipe > 0)
			write(1, "pipe ", 5);
		write(1, "heredoc>", 8);
		input = get_next_line(STDIN_FILENO);
		if (ft_strncmp(av[0], input, ft_strlen(av[0])) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		free(input);
	}
}

/* Setup the here_doc file */
void	here_doc(int ac, char **av, t_pinfo *pinfo)
{
	int		fd;

	fd = open("hd_temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Here_doc Error");
		exit(1);
	}
	write_heredoc(ac, av, fd);
	close(fd);
	pinfo->fd_in = open("hd_temp", O_RDONLY);
	if (pinfo->fd_in == -1)
	{
		unlink("hd_temp");
		perror("Here_doc Error");
		exit(1);
	}
}
