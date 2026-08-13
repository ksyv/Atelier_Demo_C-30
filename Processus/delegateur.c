#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t ouvrier_pid;
    int statut;

    char *arguments[] = {"/bin/date", NULL};
    printf("Chef: Debut de journée PID %u \n", getpid());

    ouvrier_pid = fork();

    if (ouvrier_pid == -1) {
        perror("Echec critique du clonage\n");
        return (1);
    }

    if (ouvrier_pid == 0) {
        printf("Je suis né! je vais lancer /bin/date... \n");
        if (execve(arguments[0], arguments, NULL) == -1) {
            perror("L'ouvrier n'a pas toruvé le bon outil");
            return (1);
        }
        printf("Ce texte ici ne s'affichera jamais, puisque mon contenu a été remplacé \n");

    } else {
        wait(&statut);
        printf("L'ouvrier a terminé sa tâche, on peut rentrer \n");
    }

    return (0);
}