/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:11:20 by alsanche          #+#    #+#             */
/*   Updated: 2021/12/31 16:28:06 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define	PIPEX_H

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

int main(int arc, char **arv);


#endif