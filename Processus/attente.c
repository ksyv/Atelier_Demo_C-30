#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t retour_fork;
    int statut;

    retour_fork = fork();

    if (retour_fork == -1) {
        perror("Echec critique du clonage\n");
        return (1);
    }

    if (retour_fork == 0) {
        printf("Je suis l'enfant! Je commence une tâche qui va me prendre 3sec \n");
        sleep(3);
        printf("J'ai fini!!!! \n");
    } else {
        printf("Je suis le Parent, je vais devoir attendre patiemment que mon enfant est terminé \n");
        wait(&statut);
        printf("Ça y est, l'enfant à fini, je peux donc à mon tour m'en aller et fermer le programme proprement \n");
    }

    return (0);
}