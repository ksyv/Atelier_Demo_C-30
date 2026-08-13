#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t retour_fork;
    printf("Avant le clonage... Un seul processus \n");

    retour_fork = fork();

    if (retour_fork == -1) {
        perror("Echec critique du clonage\n");
        return (1);
    }

    if (retour_fork == 0) {
        printf("Je suis l'enfant! La fonction fork m'a renvoyé 0. Mon PID est %u \n", getpid());
    } else {
        printf("Je suis le Parent, mon PID est %u. J'ai créé l'enfant au PID %u \n", getpid(), retour_fork);
    }

    return (0);
}