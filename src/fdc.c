//
// Created by 이재현 on 2025-03-17.
//

#include "pipex.h"

int	fdc_open(t_list **dyn, t_list **fds, const char *file, const int flag)
{
	int	fd;

	fd = open(file, flag);
	if (fd == -1 || !fdc_add_to_list(dyn, fds, fd))
	{
		perror(PIPEX);
		fdc_close_all(*dyn, *fds);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_pipe_rw	*fdc_pipe(t_list **dyn, t_list **fds)
{
	t_pipe_rw	*rw;
	int			_fds[2];

	if (pipe(_fds) == -1)
	{
		perror(PIPEX);
		fdc_close_all(*dyn, *fds);
		exit(EXIT_FAILURE);
	}
	rw = (t_pipe_rw *)gc_calloc(dyn, 1, sizeof(t_pipe_rw));
	if (rw == NULL)
	{
		perror(PIPEX);
		fdc_close_all(*dyn, *fds);
		exit(EXIT_FAILURE);
	}
	rw->read_end = _fds[0];
	rw->write_end = _fds[1];
	return (rw);
}

_Bool	fdc_add_to_list(t_list **dyn, t_list **fds, const int fd)
{
	t_list	*node;
	t_list	*tmp;
	int		*new_fd;

	node = gc_calloc(dyn, 1, sizeof(t_list));
	new_fd = gc_calloc(dyn, 1, sizeof(int));
	if (!node || !new_fd)
		return (0);
	*new_fd = fd;
	node->content = new_fd;
	node->next = NULL;
	if (!(*fds))
	{
		(*fds) = node;
		return (1);
	}
	tmp = *fds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}

int	fdc_close_all(t_list *dyn, t_list *fds)
{
	t_list	*curr;
	t_list	*next;
	int		res;

	curr = fds;
	res = 0;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
			res += close(*((int *)curr->content));
		curr = next;
	}
	return (gc_free_all(dyn), res);
}