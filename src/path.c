/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:55:14 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/23 14:58:25 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(t_list **dyn, char **envp)
{
	char	**path;
	char	*raw_path;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			raw_path = gc_substr(dyn, envp[i], 5, ft_strlen(envp[i]) - 5);
			if (raw_path == NULL)
				return (NULL);
			path = gc_split(dyn, raw_path, ':');
			if (path == NULL || path[0] == NULL)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_exec_path(t_list **dyn, char **path, const char *cmd)
{
	size_t	i;
	char	*temp_path;

	i = 0;
	while (path && path[i])
	{
		temp_path = gc_strjoin(dyn, path[i], "/");
		if (temp_path == NULL)
			return (NULL);
		temp_path = gc_strjoin(dyn, temp_path, cmd);
		if (temp_path != NULL && access(temp_path, X_OK) == 0)
			return (temp_path);
		i++;
	}
	return (NULL);
}
