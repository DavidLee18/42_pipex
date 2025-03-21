//
// Created by 이재현 on 2025-03-21.
//

#include "pipex_bonus.h"

char	*getln_until(t_list **dyn, char *limit)
{
	char	*str;

	str = (char *)gc_calloc(dyn, BSIZE + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_fprintf(STDOUT_FILENO, ">");
	return (getch_loop(dyn, str, limit));
}

char	*getch_loop(t_list **dyn, char *str, char *limit)
{
	ssize_t	i;
	char	*pos;

	i = read(STDIN_FILENO, str, BSIZE);
	if (i < 0)
		return (NULL);
	if (i == 0)
		return (ft_fprintf(STDERR_FILENO, "pipex_bonus: expected \'%s\', found EOF\n", limit), NULL);
	str[i] = '\0';
	pos = ft_strnstr(str, limit, BSIZE);
	if (pos == NULL)
	{
		if (str[i - 1] == '\n')
			ft_fprintf(STDOUT_FILENO, ">");
		pos = gc_calloc(dyn, BSIZE + 1, sizeof(char));
		if (pos == NULL)
			return (NULL);
		pos = getch_loop(dyn, pos, limit);
		if (pos == NULL)
			return (NULL);
		return (gc_strjoin(dyn, str, pos));
	}
	*pos = '\0';
	return (str);
}
