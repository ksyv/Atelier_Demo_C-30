#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t mon_pid = getpid();
    pid_t mon_parent = getppid();

    printf("Salut ! Mon PID est %u \n", mon_pid);
    printf("Et le PID de mon créateur est %u \n", mon_parent);

    return (0);
}
