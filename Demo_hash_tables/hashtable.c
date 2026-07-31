/* ==========================================================================
 * ATELIER : LES TABLES DE HACHAGE (HASH TABLES) EN C
 * Cas pratique : Annuaire ultra-rapide des utilisateurs d'un serveur Discord
 * 
 * Concepts clés à réviser :
 * - Fonction de hachage (Hash function) et Modulo (%)
 * - Recherche en temps constant (Complexité O(1))
 * - Gestion des collisions (avec des listes chaînées simples)
 * ========================================================================== */

#include <stdio.h>  // Pour l'affichage (printf)
#include <stdlib.h> // Pour l'allocation mémoire (malloc, free)
#include <string.h> // Pour la manipulation de chaînes (strcpy, strcmp)

// On fixe une petite taille pour forcer artificiellement des "collisions"
// (Dans un vrai système, on mettrait une taille beaucoup plus grande, ex: 10000)
#define TABLE_SIZE 10

/* --------------------------------------------------------------------------
 * 1. DÉFINITION DE LA STRUCTURE (Le Nœud Utilisateur)
 * --------------------------------------------------------------------------
 * Pourquoi utiliser un nœud de liste chaînée dans un tableau ? 
 * Pour gérer les collisions ! Si deux personnes tombent dans la même "case",
 * elles feront la queue l'une derrière l'autre grâce au pointeur 'next'.
 */
typedef struct UserNode {
    char username[50];         // La CLÉ (ce qu'on cherche)
    char role[50];             // La VALEUR (ce qu'on veut récupérer)
    struct UserNode* next;     // Le pointeur vers le suivant en cas de collision
} UserNode;

/* --------------------------------------------------------------------------
 * 2. NOTRE TABLE DE HACHAGE GLOBALE (L'annuaire)
 * --------------------------------------------------------------------------
 * C'est un tableau de 10 "tiroirs". 
 * Chaque tiroir contient un POINTEUR vers le début d'une liste chaînée.
 */
UserNode* discord_directory[TABLE_SIZE];

/* --------------------------------------------------------------------------
 * 3. LA FONCTION DE HACHAGE (La magie mathématique)
 * --------------------------------------------------------------------------
 * Son rôle : Transformer un texte (ex: "Alice") en un numéro de tiroir (ex: 3).
 * Elle doit toujours donner le même numéro pour le même texte.
 */
int hash_function(char* key) {
    int sum = 0; // On va y cumuler le "poids" du mot
    int i = 0;

    // On parcourt chaque lettre du pseudo jusqu'à la fin ('\0')
    while (key[i] != '\0') {
        sum = sum + key[i]; // On ajoute la valeur numérique (code ASCII) de la lettre
        i++;
    }

    // LE SECRET : Le modulo (%). 
    // Il donne le reste de la division par TABLE_SIZE (10).
    // Peu importe si la somme fait 42 ou 8597, le résultat sera TOUJOURS entre 0 et 9 !
    return sum % TABLE_SIZE;
}

/* --------------------------------------------------------------------------
 * 4. L'INSERTION (Le rangement)
 * --------------------------------------------------------------------------
 * On range l'utilisateur dans le bon tiroir. S'il y a déjà quelqu'un, 
 * on se place devant lui sans l'écraser.
 */
void insert_user(char* username, char* role){
    // 1. On calcule instantanément le numéro du tiroir
    int index = hash_function(username);

    // 2. On prépare la "fiche" de notre nouvel utilisateur
    UserNode* new_user = (UserNode*)malloc(sizeof(UserNode));
    strcpy(new_user->username, username);
    strcpy(new_user->role, role);

    // 3. Gestion de la collision : on insère le nouveau nœud au DÉBUT de la liste.
    // Le 'next' du nouveau pointe vers l'ancien premier élément du tiroir (qui peut être NULL).
    new_user->next = discord_directory[index];
    
    // Le nouveau nœud DEVIENT le premier élément du tiroir.
    discord_directory[index] = new_user;

    printf("Ajout de '%s' (index %d)\n", username, index);
}

/* --------------------------------------------------------------------------
 * 5. LA RECHERCHE INSTANTANÉE (La téléportation)
 * --------------------------------------------------------------------------
 * Au lieu de lire tout l'annuaire, on devine où est l'utilisateur et on s'y rend.
 */
void find_user(char* username) {
    // 1. On calcule instantanément le numéro du tiroir
    int index = hash_function(username);
    
    // 2. On regarde ce qu'il y a dans ce tiroir précis
    UserNode* current = discord_directory[index];

    // 3. On fouille uniquement ce tiroir (au cas où il y a eu des collisions)
    while (current != NULL) {
        
        // strcmp compare deux chaînes. Elle renvoie 0 si elles sont strictement identiques.
        if (strcmp(current->username, username) == 0) {
            printf("Trouvé! '%s' est index %d et son rôle est %s\n", username, index, current->role);
            return; // On a trouvé, on quitte la fonction immédiatement !
        }
        // Ce n'était pas lui ? On regarde le suivant dans la liste de ce tiroir.
        current = current->next;
    }
    
    // Si la boucle se termine, c'est qu'on a regardé tout le tiroir et qu'il n'y est pas.
    printf("=> ERREUR : Utilisateur %s est introuvable.\n", username);
}

/* --------------------------------------------------------------------------
 * 6. PROGRAMME PRINCIPAL (La simulation)
 * --------------------------------------------------------------------------
 */
int main() {
    // ÉTAPE 0 : Nettoyage de l'annuaire
    // Il est crucial de vider tous les tiroirs (mettre à NULL) avant de commencer,
    // sinon le C peut y laisser des valeurs "poubelles" de la mémoire.
    for (int i = 0; i < TABLE_SIZE; i++) {
        discord_directory[i] = NULL;
    }

    printf("--- Démarrage du serveur ---\n");

    // ÉTAPE 1 : Remplissage
    // Chacun va être envoyé dans une case calculée par la fonction de hachage.
    insert_user("Alice", "Admin");
    insert_user("Bob", "Membre");
    insert_user("Charlie", "Moderateur");
    insert_user("Dave", "VIP");

    // ÉTAPE 2 : Recherche
    printf("\n--- Recherche dans la base données ---\n");

    // Charlie existe, la fonction va calculer son tiroir et le trouver tout de suite.
    find_user("Charlie");
    
    // Robert n'existe pas. La fonction va regarder le tiroir où il *devrait* être,
    // ne pas le trouver, et nous avertir sans avoir eu besoin de lire Alice, Bob ou Dave !
    find_user("Robert");

    return 0; // Fin du programme
}