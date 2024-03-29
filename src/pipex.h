/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:11:20 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/09 15:04:45 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FD_R 0
# define FD_W 1

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_s_comand
{
	pid_t	*childs;
	char	**path;
	char	**empv;
	char	***command;
	int		n_com;
	int		ar;
	int		file_in;
	int		file_out;
}	t_s_comand;

/* main.c */

void	init_childs(t_s_comand *wolf, char **cmd, int i, char *arv);
void	pipex(t_s_comand *wolf, char **arv, char **enpv, int x);
void	ft_multi_cmd(int arc, char **arv, char **enpv, t_s_comand *wolf);
void	ft_putstr_fd(char *s, int fd);
int		main(int arc, char **arv, char **empv);

/* send_error.c */

char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free_c(char **str);
void	ft_free_all(t_s_comand *wolf);
void	send_error(int n, char *str);
size_t	ft_len(const char *c);

/* pipex_utils.c */

void	ft_test(int fd, char *path, char **comand, char **enpv);
void	ft_run(int *fd, char **comand, t_s_comand *wolf);
void	draw_command(t_s_comand *wolf, char **arv, int x);
char	*str_path(char **enpv);
char	**find_path(char **enpv);

/* split.c */

char	**ft_split(char const *s, char c);

#endif