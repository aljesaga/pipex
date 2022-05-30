/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:01:55 by alsanche          #+#    #+#             */
/*   Updated: 2022/05/30 19:09:30 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_c(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	while (i--)
	{
		free(str[i]);
	}
}

void	here_doc(char **arv, char **enpv, t_s_comand *wolf)
{
	char	temp[2];

	wolf->file_in = open(".ninja.txt", O_RDWR | O_CREAT);
	if (wolf->file_in < 0)
		ft_putstr_fd("the ninja was discovered", 1);
	wolf->file_out = open(arv[wolf->arkc], O_RDWR | O_CREAT | 0644);
	if (wolf->file_out < 0)
		send_error(0, arv[5]);
	wolf->command = malloc(sizeof(**char) * 3);
	while ()
	{
		if (ft_strcomp(STDIN_FILENO, arv[2]) != 1)
			break ;
		ft_putstr_fd(STDIN_FILENO, wolf->file_in);
	}
	pipex(wolf, arv, enpv, 1);
}
