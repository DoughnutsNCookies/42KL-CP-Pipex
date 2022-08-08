/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:36:57 by schuah            #+#    #+#             */
/*   Updated: 2022/07/23 14:16:11 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Check whether or not the file being read is here_doc, 
 * and have enough arguments for code to function properly */
int	check_hd(int ac, char **av, t_pinfo *pinfo)
{
	if (av == NULL || ac < 5)
	{
		print_error("Error: Command not found.\n");
		return (1);
	}
	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		pinfo->hd = 1;
		return (0);
	}
	pinfo->hd = 0;
	return (0);
}

/* Creates pipes and save into struct */
void	create_pipes(t_pinfo *pinfo)
{
	int	i;

	i = -1;
	while ((pinfo->ncmd - 1) > ++i)
		if (pipe(pinfo->pipe + (2 * i)) == -1)
			free_parent(pinfo);
}

/* Get neccesary info for pipping */
void	do_pipe(int ac, char **av, char **envp, t_pinfo *pinfo)
{
	pinfo->ncmd = ac - (3 + pinfo->hd);
	pinfo->npipe = 2 * (pinfo->ncmd - 1);
	pinfo->pipe = malloc(sizeof(int) * pinfo->npipe);
	if (pinfo->pipe == 0)
	{
		perror("Pipe Error");
		exit(1);
	}
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	pinfo->cmdpath = ft_split(*envp + 5, ':');
	if (pinfo->cmdpath == NULL)
		pipe_fail(pinfo);
	create_pipes(pinfo);
	pinfo->i = -1;
	while (pinfo->ncmd > ++(pinfo->i))
		produce(pinfo, av, envp);
}

/* Start of the main function */
int	main(int ac, char *av[], char *envp[])
{
	t_pinfo	pinfo;

	default_pipex_flag(&pinfo);
	if (check_hd(ac, av, &pinfo))
		return (0);
	setfd_in(ac, av, &pinfo);
	setfd_out(ac, av, &pinfo);
	do_pipe(ac, av, envp, &pinfo);
	close_pipes(&pinfo);
	waitpid(-1, NULL, 0);
	free_parent(&pinfo);
	return (0);
}
