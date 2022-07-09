/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:32:41 by alsanche          #+#    #+#             */
/*   Updated: 2022/01/10 12:32:41 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;
	int		size;

	if (!s1 || !s2)
		return (NULL);
	size = (ft_len(s1) + ft_len(s2));
	new = (char *)malloc(size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new[i++] = s2[j];
		j++;
	}
	new[i++] = '\0';
	return (new);
}

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
	free(str);
}

void	ft_free_all(t_s_comand *wolf)
{
	int	i;

	i = 0;
	wolf->ar = 0;
	while (i < wolf->n_com)
		i++;
	while (i-- > 0)
	{
		ft_free_c(wolf->command[i]);
	}
	free(wolf->command);
	if (wolf->path != NULL)
		ft_free_c(wolf->path);
	wolf->n_com = 0;
}

void	send_error(int n, char *str)
{
	char	*temp;

	if (n == 0)
	{	
		temp = ft_strjoin("zsh: permission denied: ", str);
		ft_putstr_fd(temp, 1);
		exit (EXIT_SUCCESS);
	}
	else if (n == 1)
	{
		temp = ft_strjoin("zsh: command not found: ", str);
		ft_putstr_fd(temp, 1);
	}
	else if (n == 2)
	{
		temp = ft_strjoin(str, " it doesn't work");
		ft_putstr_fd(temp, 1);
	}
	else
	{
		temp = ft_strjoin("zsh: no such file or directory: ", str);
		ft_putstr_fd(temp, 1);
	}
	free(temp);
}

size_t	ft_len(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}
