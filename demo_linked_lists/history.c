/* ==========================================================================
 * ATELIER : LES LISTES DOUBLEMENT CHAÎNÉES EN C
 * Cas pratique : Historique de navigation d'un serveur Discord
 * 
 * Concepts clés à réviser :
 * - Allocation dynamique (malloc / free)
 * - Structures (struct) et alias (typedef)
 * - Pointeurs de navigation (next, prev)
 * - Manipulation et suppression au milieu d'une chaîne
 * ========================================================================== */

#include <stdio.h>  // Pour l'affichage (printf)
#include <stdlib.h> // Pour l'allocation mémoire (malloc, free)
#include <string.h> // Pour la manipulation de chaînes (strcpy)

/* --------------------------------------------------------------------------
 * 1. DÉFINITION DE LA STRUCTURE (Le Nœud)
 * --------------------------------------------------------------------------
 * C'est la "brique" de base de notre historique.
 * Chaque nœud représente la visite d'un salon à un instant T.
 */
typedef struct Node {
    char channel_name[50];    // La donnée brute : le nom du salon (ex: "Taverne")
    
    struct Node* next;        // POINTEUR SUIVANT : Le lien vers le salon visité juste après (Marche avant)
    struct Node* prev;        // POINTEUR PRÉCÉDENT : Le lien vers le salon visité juste avant (Rétroviseur)
} Node;

/* --------------------------------------------------------------------------
 * 2. FONCTION DE CRÉATION (L'usine à nœuds)
 * --------------------------------------------------------------------------
 * Prépare un nœud tout neuf, prêt à être inséré dans la liste.
 */
Node* create_node(char* name) {
    // 1. Allocation dynamique : on demande au système la place exacte pour un "Node"
    Node* new_node = (Node*)malloc(sizeof(Node));
    
    // 2. Copie de la donnée : en C, on ne peut pas faire "=" pour des tableaux de char.
    strcpy(new_node->channel_name, name);
    
    // 3. Initialisation des pointeurs de sécurité : 
    // Par défaut, le nœud est isolé, il ne pointe vers rien (NULL).
    new_node->next = NULL;
    new_node->prev = NULL;
    
    return new_node; // On renvoie l'adresse mémoire du nœud fraîchement créé
}

/* --------------------------------------------------------------------------
 * 3. FONCTION D'AJOUT (La navigation)
 * --------------------------------------------------------------------------
 * Simule un clic sur un nouveau salon et l'accroche à la fin de notre historique.
 */
Node* visit_channel(Node* current, char* name) {
    // On crée la nouvelle brique
    Node* new_node = create_node(name);
    
    // Si on a déjà un historique (current n'est pas vide)...
    if (current != NULL) {
        // ... On fait les branchements !
        // Le salon sur lequel on était pointe "en avant" vers le nouveau salon
        current->next = new_node;
        
        // Le nouveau salon pointe "en arrière" vers l'ancien (la magie de la liste double !)
        new_node->prev = current;
    }
    
    printf("-> visite de : %s\n", name);

    // Le nouveau salon devient notre position actuelle, on le renvoie
    return new_node;
}

/* --------------------------------------------------------------------------
 * 4. FONCTION DE SUPPRESSION (La chirurgie)
 * --------------------------------------------------------------------------
 * Supprime un nœud sans briser la chaîne, en reconnectant les voisins entre eux.
 */
void delete_node(Node* node_to_delete) {
    // Sécurité de base : si on demande à supprimer du vide, on annule.
    if (node_to_delete == NULL) return;

    printf("Suppression du salon %s de l'historique \n", node_to_delete->channel_name);
    
    // Étape A : Raccorder le nœud PRÉCÉDENT
    if (node_to_delete->prev != NULL) {
        // Le 'next' du précédent enjambe le nœud actuel pour pointer sur le suivant
        node_to_delete->prev->next = node_to_delete->next;
    }

    // Étape B : Raccorder le nœud SUIVANT
    if (node_to_delete->next != NULL) {
        // Le 'prev' du suivant enjambe le nœud actuel pour pointer sur le précédent
        node_to_delete->next->prev = node_to_delete->prev;
    }

    // Étape C : Destruction
    // Maintenant que les voisins sont connectés entre eux, on peut détruire le nœud en toute sécurité.
    free(node_to_delete);
}

/* --------------------------------------------------------------------------
 * 5. PROGRAMME PRINCIPAL (La simulation)
 * --------------------------------------------------------------------------
 */
int main(){
    // ÉTAPE 1 : Construction de l'historique de base
    // Le premier appel prend "NULL" car il n'y a pas d'historique précédent.
    Node* current = visit_channel(NULL, "General");
    current = visit_channel(current, "Taverne");
    current = visit_channel(current, "Campement");
    current = visit_channel(current, "Ressources");
    // À ce stade, current est sur "Ressources". La liste est : 
    // General <=> Taverne <=> Campement <=> Ressources

    // ÉTAPE 2 : Simulation des boutons "Retour" et "Suivant"
    printf("\n--Test du bouton precedent\n");
    printf("Je suis actuellement dans %s\n", current->channel_name); // Ressources

    current = current->prev; // Clic !
    printf("Je suis maintenant dans le channel %s\n", current->channel_name); // Campement

    current = current->prev; // Clic !
    printf("Je suis maintenant dans le channel %s\n", current->channel_name); // Taverne

    current = current->next; // Clic en avant !
    printf("Je suis maintenant dans le channel %s\n", current->channel_name); // Retour sur Campement

    // ÉTAPE 3 : La suppression
    // On isole le pointeur de la Taverne (qui est juste derrière nous) pour l'exemple.
    Node* taverne = current->prev;

    printf("\n---Suppression---\n");
    delete_node(taverne); 
    // La liste devient : General <=> Campement <=> Ressources

    // ÉTAPE 4 : Affichage final
    // Pour afficher depuis le début, il faut "rembobiner" le curseur tout à gauche
    while(current->prev != NULL) {
        current = current->prev;
    }

    // Une fois au début, on lit de gauche à droite grâce aux pointeurs 'next'
    printf("\nNouvel historique tout neuf\n");
    while (current != NULL) {
        printf("[%s] <=> ", current->channel_name);
        current = current->next;
    }
    printf("FIN\n");

    return 0; // Fin du programme, la mémoire allouée par l'OS sera nettoyée automatiquement à la fermeture.
}