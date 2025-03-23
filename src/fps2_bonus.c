//
// Created by 이재현 on 2025-03-21.
//

#include "pipex_bonus.h"

char	*getln_until(t_list **dyn, char *limit)
{
	char	*str;
	char	*temp;

	str = "";
	ft_fprintf(STDOUT_FILENO, ">");
	temp = gc_getline(dyn, STDIN_FILENO);
	while (temp != NULL && ft_strcmp(gc_strtrim(dyn, temp, "\n"), limit) != 0)
	{
		str = gc_strjoin(dyn, str, temp);
		ft_fprintf(STDOUT_FILENO, ">");
		temp = gc_getline(dyn, STDIN_FILENO);
	}
	if (temp == NULL || ft_strcmp(gc_strtrim(dyn, temp, "\n"), limit) != 0)
		return (ft_fprintf(STDERR_FILENO, "%s: expected \'%s\', got EOF", PIPEX, limit), NULL);
	return (str);
}
