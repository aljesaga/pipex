#include "pipex_bonus.h"

void    print_lista(t_s_comand *wolf)
{
    int i = 0;

    printf("|---------|---------------|----------|\n");
    printf("%d\n", wolf->n_com);
    printf("%d\n", wolf->ar);
    printf("----->%d\n", wolf->file_in);
    printf("----->%d\n", wolf->file_out);
    while (i < wolf->n_com)
    {
        printf("coman---->%s\n", wolf->command[i][0]);
        i++;
    }
    //printf("%d\n", wolf->fd[0]);
    //printf("%d\n", wolf->fd[1]);
}
