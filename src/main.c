//
// Created by 이재현 on 2025-03-16.
//

#include "pipex.h"

int main(const int argc, char **argv, char **envp)
{
	int			fps[4];
	t_list		*dyn;
	t_list		*fds;
	pid_t		pids[2];

	dyn = NULL;
	fds = NULL;
	if (argc != 5)
		return (ft_fprintf(STDERR_FILENO, "there should be 4 args..\n"), EXIT_FAILURE);
	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
		return (perror(PIPEX), EXIT_FAILURE);
	else if (access(argv[1], R_OK) == -1)
		perror(PIPEX);
	if (pipe(fps) == -1)
		return (perror(PIPEX), EXIT_FAILURE);
	fps[2] = fdc_open(&dyn, &fds, argv[1], O_RDONLY);
	fps[3] = fdc_open(&dyn, &fds, argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	pids[0] = exec1((t_list*[]){ dyn, fds }, argv[2], fps, envp);
	pids[1] = exec2((t_list*[]){ dyn, fds }, argv[3], fps, envp);
	close_wait(fps, pids);
	return (fdc_close_all(dyn, fds), EXIT_SUCCESS);
}

pid_t	exec1(t_list *dyn_fds[2], const char *cmd, int fps[4], char **envp)
{
	pid_t	id;
	char	**argv;

	argv = gc_split(&dyn_fds[0], cmd, ' ');
	if (argv == NULL || access(argv[0], X_OK) == -1)
		return (perror("pipex.exec1"), -1);
	id = fork();
	if (id == -1)
		return (perror(PIPEX), -1);
	if (id == 0)
	{
		close(fps[0]);
		if (dup2(fps[1], STDOUT_FILENO) == -1 || dup2(fps[2], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		execve(argv[0], argv, envp);
		exit(EXIT_FAILURE);
	}
	return (id);
}

pid_t	exec2(t_list *dyn_fds[2], const char *cmd, int fps[4], char **envp)
{
	pid_t	id;
	char	**argv;

	argv = gc_split(&dyn_fds[0], cmd, ' ');
	if (argv == NULL || access(argv[0], X_OK) == -1)
		return (perror("pipex.exec2"), -1);
	id = fork();
	if (id == -1)
		return (perror(PIPEX), -1);
	if (id == 0)
	{
		close(fps[1]);
		if (dup2(fps[0], STDIN_FILENO) == -1 || dup2(fps[3], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		execve(argv[0], argv, envp);
		exit(EXIT_FAILURE);
	}
	return (id);
}

void	close_wait(int fps[4], pid_t pids[2])
{
	close(fps[0]);
	close(fps[1]);
	close(fps[2]);
	close(fps[3]);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}