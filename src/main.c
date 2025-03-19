//
// Created by 이재현 on 2025-03-16.
//

#include "pipex.h"

int main(const int argc, const char **argv, char **envp)
{
	int			files[2];
	t_list		*dyn;
	t_list		*fds;
	t_pipe_rw	**rw;
	pid_t		pids[2];
	char		**argv1;

	dyn = NULL;
	fds = NULL;
	if (argc < 5)
		return (ft_fprintf(STDERR_FILENO, "too few args!\n"), EXIT_FAILURE);
	if (access(argv[1], R_OK) == -1 || (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1))
		return (perror(PIPEX), EXIT_FAILURE);
	files[0] = fdc_open(&dyn, &fds, argv[1], O_RDONLY);
	rw = (t_pipe_rw **)gc_calloc(&dyn, 1, sizeof(t_pipe_rw *));
	if (rw == NULL)
		return (ft_fprintf(STDERR_FILENO, "alloc fail\n"), EXIT_FAILURE);
	rw[0] = fdc_pipe(&dyn, &fds);
	files[1] = fdc_open(&dyn, &fds, argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	pids[0] = fork();
	if (pids[0] == -1)
		return (perror(PIPEX), fdc_close_all(dyn, fds), EXIT_FAILURE);
	if (pids[0] == 0)
	{
		close(rw[0]->read_end);
		argv1 = gc_split(&dyn, argv[2], ' ');
		if (argv1 == NULL || dup2(rw[0]->write_end, STDOUT_FILENO) == -1 || dup2(files[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		execve(argv1[0], argv1, envp);
		exit(EXIT_FAILURE);
	}
	pids[1] = fork();
	if (pids[1] == -1)
		return (perror(PIPEX), fdc_close_all(dyn, fds), EXIT_FAILURE);
	if (pids[1] == 0)
	{
		close(rw[0]->write_end);
		argv1 = gc_split(&dyn, argv[3], ' ');
		if (argv1 == NULL || dup2(rw[0]->read_end, STDIN_FILENO) == -1 || dup2(files[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		execve(argv1[0], argv1, envp);
		exit(EXIT_FAILURE);
	}
	close(rw[0]->write_end);
	close(rw[0]->read_end);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	return (fdc_close_all(dyn, fds), EXIT_SUCCESS);
}