//
// Created by 이재현 on 2025-03-16.
//

#ifndef PIPEX_H
#define PIPEX_H
#include "../ft_printf/src/ft_printf.h"
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#define PIPEX "pipex_bonus"
#endif //PIPEX_H

typedef struct s_pipe_rw
{
	int	write_end;
	int	read_end;
}	t_pipe_rw;

int			fdc_open(t_list **dyn, t_list **fds, const char *file, int flag);

t_pipe_rw	*fdc_pipe(t_list **dyn, t_list **fds);

int			fdc_close_all(t_list *dyn, t_list *fds);

_Bool		fdc_add_to_list(t_list **dyn, t_list **fds, int fd);

pid_t		exec_n(t_list **dyn, char **arg_env[2], t_vec *fps, size_t n);

void		exec_cmds(t_list **dyn, char **arg_env[2], t_vec *fps);

void		close_wait(t_list *dyn, t_vec *fps);

char		**get_path(t_list **dyn, char **envp);

char		*get_exec_path(t_list **dyn, char **path, const char *cmd);

int			open_pipes(const t_vec *fps);

void		fps_close(t_list *dyn, t_vec *fps);

void		close_pipes(t_vec *fps, size_t except);

void		fill_zeros(t_list **dyn, t_vec *fps, size_t len);

int			open_files(t_vec *fps, t_list **dyn, char **inf, char *outf);

char		*getln_until(t_list **dyn, char *limit);

void		fps_close_all(t_list *dyn, t_vec *fps);
