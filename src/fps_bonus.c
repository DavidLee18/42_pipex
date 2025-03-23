/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:55:14 by jaehylee          #+#    #+#             */
/*   Updated: 2025/03/23 14:59:07 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fps_close(t_list *dyn, t_vec *fps)
{
	size_t	i;

	i = 0;
	while (++i < fps->len - 1)
		close(fps->ptr[i]);
	gc_free_all(dyn);
}

void	close_pipes(t_vec *fps, size_t except)
{
	size_t	i;

	i = 0;
	while (i < fps->len)
	{
		if (i != 2 * except && i != 2 * except + 1)
			close(fps->ptr[i]);
		i++;
	}
}

void	fill_zeros(t_list **dyn, t_vec *fps, size_t len)
{
	size_t	i;

	i = 0;
	while (++i <= len)
		push_back(dyn, fps, 0);
}

int	open_files(t_vec *fps, t_list **dyn, char **inf, char *outf)
{
	int		fp[2];
	char	*temp;

	if (ft_strcmp(*inf, "here_doc") == 0)
	{
		if (pipe(fp) == -1)
			return (-1);
		fps->ptr[0] = fp[0];
		fps->ptr[fps->len - 1] = open(outf, O_WRONLY | O_CREAT | O_APPEND);
		temp = getln_until(dyn, inf[1]);
		if (temp == NULL)
			return (close(fp[0]), close(fp[1]), -1);
		ft_fprintf(fp[1], temp);
		return (close(fp[1]), 0);
	}
	fps->ptr[0] = open(*inf, O_RDONLY);
	fps->ptr[fps->len - 1] = open(outf, O_WRONLY | O_CREAT | O_TRUNC);
	return (0);
}

void	fps_close_all(t_list *dyn, t_vec *fps)
{
	size_t	i;

	i = 0;
	while (i < fps->len)
	{
		close(fps->ptr[i]);
		i++;
	}
	gc_free_all(dyn);
}
