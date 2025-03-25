/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:55:14 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/25 15:48:33 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(const int argc, char **argv, char **envp)
{
	int			fps[4];
	t_list		*dyn;
	pid_t		pids[2];

	dyn = NULL;
	if (argc != 5)
		return (ft_fprintf(STDERR_FILENO, "there should be 4 args..\n"),
			EXIT_FAILURE);
	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
		return (perror(PIPEX), EXIT_FAILURE);
	else if (access(argv[1], R_OK) == -1)
		perror(PIPEX);
	if (pipe(fps) == -1)
		return (perror(PIPEX), EXIT_FAILURE);
	fps[2] = open(argv[1], O_RDONLY);
	fps[3] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	pids[0] = exec1(&dyn, argv[2], fps, envp);
	pids[1] = exec2(&dyn, argv[3], fps, envp);
	return (close_wait(&dyn, fps, pids), EXIT_SUCCESS);
}

pid_t	exec1(t_list **dyn, const char *cmd, int fps[4], char **envp)
{
	pid_t	id;
	char	**argv;
	char	*absol_path;

	argv = gc_split(dyn, cmd, ' ');
	if (argv == NULL)
		return (perror(PIPEX), -1);
	absol_path = get_exec_path(dyn, get_path(dyn, envp),
			argv[0]);
	if (absol_path == NULL)
		return (perror(PIPEX), -1);
	id = fork();
	if (id == -1)
		return (perror(PIPEX), -1);
	if (id == 0)
	{
		close(fps[0]);
		if (dup2(fps[1], STDOUT_FILENO) == -1 || dup2(fps[2],
				STDIN_FILENO) == -1)
			(gc_free_all(*dyn), exit(EXIT_FAILURE));
		execve(absol_path, argv, envp);
		gc_free_all(*dyn);
		exit(EXIT_FAILURE);
	}
	return (id);
}

pid_t	exec2(t_list **dyn, const char *cmd, int fps[4], char **envp)
{
	pid_t	id;
	char	**argv;
	char	*absol_path;

	argv = gc_split(dyn, cmd, ' ');
	if (argv == NULL)
		return (perror(PIPEX), -1);
	absol_path = get_exec_path(dyn, get_path(dyn, envp),
			argv[0]);
	if (absol_path == NULL)
		return (perror(PIPEX), -1);
	id = fork();
	if (id == -1)
		return (perror(PIPEX), -1);
	if (id == 0)
	{
		close(fps[1]);
		if (dup2(fps[0], STDIN_FILENO) == -1 || dup2(fps[3],
				STDOUT_FILENO) == -1)
			(gc_free_all(*dyn), exit(EXIT_FAILURE));
		execve(absol_path, argv, envp);
		gc_free_all(*dyn);
		exit(EXIT_FAILURE);
	}
	return (id);
}

void	close_wait(t_list **dyn, int fps[4], pid_t pids[2])
{
	close(fps[0]);
	close(fps[1]);
	close(fps[2]);
	close(fps[3]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	gc_free_all(*dyn);
}
