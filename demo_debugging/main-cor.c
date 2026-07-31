#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int score;
} Student;


int main() {
    int num_students = 3;
    int total_score;
    int i = 0;
    int j = 0;
    
    // Allocation du tableau d'étudiants
    Student *classroom = malloc(num_students * sizeof(Student));
    if (classroom == NULL) {
        fprintf(stderr, "erreur d'allocation mémoire pour classroom\n");
        return 1;
    }

    // Initialisation des étudiants
    for (i = 0; i < num_students; i++) {
        classroom[i].name = malloc(50 * sizeof(char));
        if (classroom[i].name == NULL) {
            fprintf(stderr, "erreur d'allocation mémoire pour classroom\n");
            for (j = 0; j < i; j++) {
            free(classroom[j].name);
        }
        free(classroom);
        return 1;
        }
        sprintf(classroom[i].name, "Etudiant_%d", i);
        classroom[i].score = 50 + (i * 10);
        total_score += classroom[i].score;
    }

    // Calcul et affichage de la moyenne
    float average = (float)total_score / num_students;
    printf("La moyenne de la classe est de : %.2f\n", average);

    for (i = 0; i < num_students; i++) {
        free(classroom[i].name);
    }

    // Nettoyage de la mémoire
    free(classroom);

    return 0;
}
