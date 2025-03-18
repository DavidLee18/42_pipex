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
#define PIPEX "pipex"
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