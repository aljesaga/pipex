/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:11:20 by alsanche          #+#    #+#             */
/*   Updated: 2022/02/23 16:07:07 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define    FD_R 0
# define    FD_W 1

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "../Libft/libft.h"

/* main.c */

void	ft_test(int fd, char *path, char **comand, char **enpv);
void	ft_romulo(int *fd, int file, char **comand, char **enpv);
void	ft_remo(int *fd, int file, char **comand, char **enpv);
void	pipex(int *file, char **arv, char **enpv);
int		main(int arc, char **arv, char **empv);

/* send_error.c */

char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free_all(char **str);
void	send_error(int n, char *str);
char	*str_path(char **enpv);
char	**find_path(char **enpv);

#endif