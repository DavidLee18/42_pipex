/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:55:14 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/23 14:56:41 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (ft_fprintf(STDERR_FILENO, "%s: expected \'%s\', got EOF", PIPEX,
				limit), NULL);
	return (str);
}
