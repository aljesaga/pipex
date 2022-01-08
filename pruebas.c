# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

int main(void)
{
    int  fd[2];
    char *argv[] = {"ls", "-la", "/home/alsanche/pipex", 0};
    char *envp[] = {"PATH=/bin", 0};

    pipe(fd);
    close(fd[1]);
    fd[0] = open("file2.txt", O_WRONLY);
    dup2(fd[0], STDOUT_FILENO);
    execve("/bin/ls", argv, envp);
    close(fd[0]);
    return (0);
}