/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:55:14 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/24 18:50:23 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(const int argc, char **argv, char **envp)
{
	t_vec		fps;
	t_list		*dyn;

	dyn = NULL;
	fps = (t_vec){.ptr = NULL, .len = 0, .cap = 0};
	if (argc < 5)
		return (ft_fprintf(STDERR_FILENO, "too few args!\n"), EXIT_FAILURE);
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) == -1)
		return (perror(PIPEX), EXIT_FAILURE);
	if (ft_strcmp(argv[1], "here_doc") && access(argv[1], R_OK) == -1)
		perror(PIPEX);
	fill_zeros(&dyn, &fps, 2 * (argc - 3 - (ft_strcmp(argv[1],
					"here_doc") == 0)));
	if (open_pipes(&fps) == -1)
		return (perror(PIPEX), fps_close_all(&dyn, &fps), EXIT_FAILURE);
	if (open_files(&fps, &dyn, argv + 1, argv[argc - 1]) == -1)
		return (perror(PIPEX), fps_close_all(&dyn, &fps), EXIT_FAILURE);
	exec_cmds(&dyn, (char **[]){argv, envp}, &fps);
	return (close_wait(&dyn, &fps), EXIT_SUCCESS);
}

int	open_pipes(const t_vec *fps)
{
	size_t	i;
	int		temp;

	i = 0;
	while (i < fps->len / 2 - 1)
	{
		if (pipe(fps->ptr + 2 * i + 1) == -1)
			return (-1);
		temp = fps->ptr[2 * i + 1];
		fps->ptr[2 * i + 1] = fps->ptr[2 * i + 2];
		fps->ptr[2 * i + 2] = temp;
		i++;
	}
	return (0);
}

void	exec_cmds(t_list **dyn, char **arg_env[2], t_vec *fps)
{
	size_t	i;

	i = 0;
	while (i < fps->len / 2)
	{
		if (exec_n(dyn, arg_env, fps, i) == -1)
		{
			fps_close_all(dyn, fps);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

pid_t	exec_n(t_list **dyn, char **arg_env[2], t_vec *fps, size_t n)
{
	pid_t	id;
	char	**argv;
	char	*absol_path;

	argv = gc_split(dyn, arg_env[0][n + 2 + (ft_strcmp(arg_env[0][1],
					"here_doc") == 0)], ' ');
	if (argv == NULL)
		return (perror(PIPEX), -1);
	absol_path = get_exec_path(dyn, get_path(dyn, arg_env[1]), argv[0]);
	if (absol_path == NULL)
		return (perror(PIPEX), -1);
	id = fork();
	if (id == -1)
		return (perror(PIPEX), -1);
	if (id == 0)
	{
		close_pipes(fps, n);
		if (dup2(fps->ptr[2 * n], STDIN_FILENO) == -1
			|| dup2(fps->ptr[2 * n + 1], STDOUT_FILENO) == -1)
			(gc_free_all(*dyn), exit(EXIT_FAILURE));
		execve(absol_path, argv, arg_env[1]);
		gc_free_all(*dyn);
		exit(EXIT_FAILURE);
	}
	return (id);
}

void	close_wait(t_list **dyn, t_vec *fps)
{
	fps_close_all(dyn, fps);
	waitpid(-1, NULL, 0);
}
